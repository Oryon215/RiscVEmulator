#include "../../headers/cpu.h"
/*
Manager program Traps (interrupts, exceptions)
*/

void RaiseInterrupt(State* s, unsigned char error_code)
{
     /*
    RaiseInterrupt - Raises an interrupt with a given error code.
    s - the current state of the CPU
    error_code - the error code to raise as an interrupt
    return: void
    */
    s->csr[mip] = ChangeBit(s->csr[mip], 1, error_code + 1);
}

void S_Catch(State* s, unsigned char error_code, unsigned char exception)
{
    /*
    S_Catch - Handles supervisor mode interrupts and exceptions.
    s - the current state of the CPU
    error_code - the error code of the interrupt/exception
    exception - flag indicating whether it is an exception (1) or an interrupt (0)
    return: void
    */
    if (!exception)
    {
        if ((s->csr[sie] >> error_code) && (s->csr[sip] >> error_code))
        {
            return;
        }
        s->csr[sie] = ChangeBit(s->csr[sie], 1, -(error_code + 1));
        s->csr[sip] = ChangeBit(s->csr[sip], 1, -(error_code + 1));
    }
    else
    {
        if (error_code >=0 && error_code <=7 && error_code != 3)
        {
            s->csr[sbadaddr] = s->pc;
        }
    }

    s->csr[sepc] = s->pc;
    s->csr[scause] = (exception << 31) | error_code;

    ((void (*)(State*, unsigned char, unsigned char))(s->csr[stvec]))(s, error_code, exception);

    s->csr[sie] = ChangeBit(s->csr[sie], 1, error_code + 1);
    s->csr[sip] = ChangeBit(s->csr[sip], 1, error_code + 1);

}

void M_Catch(State* s, unsigned char error_code, unsigned char exception)
{
    /*
    M_Catch - Handles machine mode interrupts and exceptions.
    s - the current state of the CPU
    error_code - the error code of the interrupt/exception
    exception - flag indicating whether it is an exception (1) or an interrupt (0)
    return: void
    */
    char delegation;
    if (!exception)
    {
        if ((s->csr[mie] >> error_code) && (s->csr[mip] >> error_code))
        {
            return;
        }
        s->csr[mstatus] = ChangeBit(s->csr[mstatus], 3, -12, -8, -4); //turn off MPP, MPIE, MIE
        delegation = (s->csr[mideleg] >> error_code) & 1;
        s->csr[mie] = ChangeBit(s->csr[mie], 1, -(error_code + 1));
        s->csr[mip] = ChangeBit(s->csr[mip], 1, -(error_code + 1));
    }
    else
    {
        delegation = (s->csr[medeleg] >> error_code) & 1;
        if (error_code >=0 && error_code <=7 && error_code != 3)
        {
            s->csr[mbadaddr] = s->pc;
        }
    }

    s->csr[mepc] = s->pc;
    s->csr[mcause] = (exception << 31) | error_code;

    if (delegation && !exception)
    {
        s->csr[sip] = ChangeBit(s->csr[sip], 1, error_code + 1);
        s->csr[sie] = ChangeBit(s->csr[sie], 1, error_code + 1);
    }
    else if (delegation)
    {
        S_Catch(s, error_code, exception);
    }
    else
    {
        ((void (*)(State*, unsigned char, unsigned char))(s->csr[mtvec]))(s, error_code, exception);
    }

    s->csr[mie] = ChangeBit(s->csr[mie], 1, error_code + 1);
    s->csr[mip] = ChangeBit(s->csr[mip], 1, error_code + 1);

}

void MIVT(State* s, unsigned char error_code, unsigned char exception)
{
    /*
    MIVT - Machine Interrupt Vector Table
    Handles specific machine mode exceptions by printing error messages and terminating the program.
    s - the current state of the CPU
    error_code - the error code of the exception
    exception - flag indicating whether it is an exception (1) or an interrupt (0)
    return: void
    */
    if (!exception)
    {

    }
    else
    {
        switch (error_code)
        {
        case 0: // instruction address misaligned
            printf("Instruction address misaligned at %x.\nProgram terminated.\n", s->pc);
            exit(0);
        case 1: // instruction access fault
            printf("Instruction access fault at %x.\nProgram terminated.\n", s->pc);
            exit(0);
        case 2: // illegal instruction
        {
            unsigned int cmd = *(unsigned int*)(s->memory + s->pc);
            UnimplementedInstruction(cmd, s);
            exit(0);
        }
        case 3: // breakpoint
            // not implemented yet
            break;
        case 5: // load access fault
            printf("Load access fault at %x.\nProgram terminated.\n", s->pc);
            exit(0);
        case 6: //Store/AMO address misaligned
            // not implemented
            break;
        case 7: // Store/AMO access fault
            printf("Store access fault at %x.\nProgram terminated.\n", s->pc);
            exit(0);
        case 8: // Supervisor Environment Call
            // to be implemented by tool
            break;
        }
    }
}

void SIVT(State* s, unsigned char error_code, unsigned char exception)
{
     /*
    SIVT - Supervisor Interrupt Vector Table
    Handles specific supervisor mode exceptions, such as system calls.
    s - the current state of the CPU
    error_code - the error code of the exception
    exception - flag indicating whether it is an exception (1) or an interrupt (0)
    return: void
    */
    if (!exception)
    {
    }
    else
    {
        switch (error_code)
        {
            case 8:
                Syscall_Table(s);
        }
    }
}

char ECALL(CMD cmd, State* s)
{
    /*
    ECALL - Environment call
    Triggers an environment call, typically used for system calls or other system-level functions.
    cmd - the command containing the instruction
    s - the current state of the CPU
    return: 1 on success
    */
    M_Catch(s, 8, 1);
    //printf("ECALL\n");
    return 1;

}


