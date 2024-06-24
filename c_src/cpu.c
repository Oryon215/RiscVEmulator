#include "../headers/cpu.h"
#include "../headers/str.h"
/*
Manage Emulator Operations
*/

char instruction[60];

void UnimplementedInstruction(CMD cmd, State* s)
{
    /*
    print address and content of unimplemented instruction
    cmd - instruction contents
    s - process state
    */
    printf("Error. Unrecognized instruction in %x.\nInstruction encoding: %x.\n", s->pc, cmd);
}

void EmulateInstruction(CMD cmd, State* s){
    /*
    change state according to cmd
    cmd - instruction contents
    s - process state
    return: void
    */
    //printf("pc=%x\n", s->pc);
    //printf("ip=%x\n", cmd);
    CheckBreapoints(s);
    char opcode = cmd & get_n(7);
    char known = 0;
    switch (opcode) {
        case 0b0110111:
        {
            known = LUI(cmd, s);
            break;
        }
        case 0b0010111:
        {
            known = AUIPC(cmd, s);
            break;
        }
        case 0b1101111:
        {
            known = JAL(cmd, s);
            break;
        }
        case 0b1100111:
        {
            known = JALR(cmd, s);
            break;
        }
        case 0b1100011:
        {
            known = CJUMPS(cmd, s);
            break;
        }
        case 0b0000011:
        {
            known = LOAD(cmd, s);
            break;
        }
        case 0b0100011:
        {
            known = STORE(cmd, s);
            break;
        }
        case 0b0010011: //immediate arithmetic and logic operations
        {
            known = ALUI(cmd, s);
            break;
        }
        case 0b0110011: // arithmetic and logical operations
        {
            known = ALU(cmd, s) || MULDIV(cmd, s);
            break;
        }
        case 0b1110011: // ecall
        {
            known = ECALL(cmd, s);
            break;
        }
    }
    if (!known)
        M_Catch(s, 2, 1);
    s->pc += 4;
    s->general_purpose[zero] = 0;
    //printf("%s\n", instruction);
}

void PrintState(State* s) {
    /*
    print current process registers
    s - current process state
    return: void
    */
    for (int i = 0; i < 32; i++) {
        printf("x%d=%d ", i, s->general_purpose[i]);
        if (i % 4 == 0 && i != 0)
        {
            printf("\n");
        }
    }
    printf("pc=0x%x\n", s->pc);
    //PrintHexString(s->memory, s->memory_size);
    printf("\n");
}

int EmulateRiscV(State* s)
{
    /*
    Run a program from start to finish
    s - current program state
    return: 0
    */
    PrintState(s);
    InitAddOn(s);
    for (int i = 0; i < s->memory_size /4 ; i++)
    {
        AddOn(s);
        CheckOperation(s, X, s->pc, 1);
        //Break(s, s->pc);
        CMD cmd = *(CMD*)(s->memory + s->pc);
        EmulateInstruction(cmd , s);
        //PrintState(s);
    }
    return 0;
}

void HandlePermissionException(State* s, char operation)
{
    /*
    Handle memory access exceptions
    s - current program state
    operation - type of memory operation (R, W, X)
    return: void
    */
    if (operation == R)
        M_Catch(s, 5, 1);
    else if (operation == W)
        M_Catch(s, 7, 1);
    else
        M_Catch(s, 1, 1);
}

char CheckOperation(State* s, char operation, Address addr, char exception)
{
    /*
    check if memory operation is permitted
    s - current memory state
    operation - memory operation
    addr - memory address
    char exception - raise exception if not 0
    return: operation permitted or not.
    */
    int i;
    for (i = 0; i < s->segment_count; i++)
    {
        int lower_bound = s->memory_segments[i].addr;
        int upper_bound = s->memory_segments[i].addr + s->memory_segments[i].size;
        if (in_range(lower_bound, addr, upper_bound))
        {
            if ((s->memory_segments[i].permissions >> operation) & 1)
                return 1;
            goto lable;
        }
    }
    if (in_range(s->base_address, addr, s->memory_size))
    {
        return 1;
    }
    lable:
    if (exception)
    {
        HandlePermissionException(s, operation);
    }
    return 0;
}


