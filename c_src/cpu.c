#include "../headers/cpu.h"
#include "../headers/str.h"

char* instruction[32];

void UnimplementedInstruction(int cmd, State* state)
{
    printf("Error. Unrecognized instruction in %d.\nInstruction encoding: %x.\n", state->pc, cmd);
}

void EmulateInstruction(State* state){
    CheckOperation(state, X, state->pc, 1);
    //Break(state, state->pc);
    unsigned int cmd = *(unsigned int*)(state->memory + state->pc);
    //printf("ip=%x\n", cmd);
    CheckBreapoints(state);
    char opcode = cmd & get_n(7);
    char known = 0;
    switch (opcode) {
        case 0b0110111:
        {
            known = LUI(cmd, state);
            break;
        }
        case 0b0010111:
        {
            known = AUIPC(cmd, state);
            break;
        }
        case 0b1101111:
        {
            known = JAL(cmd, state);
            break;
        }
        case 0b1100111:
        {
            known = JALR(cmd, state);
            break;
        }
        case 0b1100011:
        {
            known = CJUMPS(cmd, state);
            break;
        }
        case 0b0000011:
        {
            known = LOAD(cmd, state);
            break;
        }
        case 0b0100011:
        {
            known = STORE(cmd, state);
            break;
        }
        case 0b0010011: //immediate arithmetic and logic operations
        {
            known = ALUI(cmd, state);
            break;
        }
        case 0b0110011: // arithmetic and logical operations
        {
            known = ALU(cmd, state) || MULDIV(cmd, state);
            break;
        }
        case 0b1110011: // ecall
        {
            known = ECALL(cmd, state);
            break;
        }
    }
    if (!known)
        M_Catch(state, 2, 1);
    state->pc += 4;
    state->general_purpose[zero] = 0;
}

void PrintState(State* state) {
    for (int i = 0; i < 32; i++) {
        printf("x%d=%d ", i, state->general_purpose[i]);
        if (i % 4 == 0 && i != 0)
        {
            printf("\n");
        }
    }
    printf("pc=0x%x\n", state->pc);
    //PrintHexString(state->memory, state->memory_size);
    printf("\n");
}


int EmulateRiscV(State* state)
{
    PrintState(state);
    for (int i = 0; i < state->memory_size /4 ; i++)
    {
        EmulateInstruction(state);
        //PrintState(state);
    }
}

void HandlePermissionException(State* s, char operation)
{
    if (operation == R)
        M_Catch(s, 5, 1);
    else if (operation == W)
        M_Catch(s, 7, 1);
    else
        M_Catch(s, 1, 1);
}

char CheckOperation(State* s, char operation, int addr, char exception)
{
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


