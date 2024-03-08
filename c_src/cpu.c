#include "cpu.h"
#include "str.h"


void UnimplementedInstruction(int cmd, State* state)
{
    printf("Error. Unrecognized instruction in %x.\nInstruction encoding: %x.\n", state->pc, cmd);
}

void EmulateInstruction(State* state) {
    unsigned int cmd = *(unsigned int*)(state->memory + state->pc);
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
            known = ALU(cmd, state);
            break;
        }

    }
    if (!known)
        UnimplementedInstruction(cmd, state);
    state->pc += 4;
}

void PrintState(State* state) {
    for (int i = 0; i < 32; i++) {
        printf("x%d=%d ", i, state->general_purpose[i]);
        if (i % 5 == 0)
        {
            printf("\n");
        }
    }
    printf("pc=%d\n", state->pc);
    PrintHexString(state->memory, state->memory_size);
    printf("\n");
}


int EmulateRiscV(State* state)
{
    PrintState(state);
    for (int i = 0; i < state->memory_size /4 ; i++)
    {
        EmulateInstruction(state);
        PrintState(state);
    }
}


