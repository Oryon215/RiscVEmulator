#include "cpu.h"

void PrintState(State* state) {
    for (int i = 0; i < 32; i++) {
        printf("x%d=%d ", i, state->general_purpose[i]);
        if (i % 4 == 3)
        {
            printf("\n");
        }
    }
    printf("pc=%d\n", state->pc);
}


int EmulateRiscV(State* state)
{
    PrintState(state);
    EmulateInstruction(state);
    PrintState(state);
}

void UnimplementedInstruction(int cmd, State* state)
{
    printf("Error. Unrecognized instruction in %h.\n Instruction encoding:%h", cmd, state->pc);
}

void EmulateInstruction(State* state) {
    unsigned int cmd = *(unsigned int*)(state->memory + state->pc);
    char opcode = cmd & get_n(7);
    char known = 0;
    switch (opcode) {
        case 0b0110111:
        {
            known = LUI(cmd, state);
        }
        case 0b0010111:
        {
            known = AUIPC(cmd, state);
        }
        case 0b1101111:
        {
            known = JAL(cmd, state);
        }
        case 0b1100111:
        {
            known = JALR(cmd, state);
        }
        case 0b1100011:
        {
            known = CJUMPS(cmd, state);
        }
        case 0b0000011:
        {
            known = LOAD(cmd, state);
        }
        case 0b0100011:
        {
            known = STORE(cmd, state);
        }
        case 0b0010011: //immediate arithmetic and logic operations
        {
            known = ALUI(cmd, state);
        }
        case 0b0110011: // arithmetic and logical operations
        {
            known = ALU(cmd, state);
        }

    }
    if (!known)
        UnimplementedInstruction(cmd, state);
    state->pc += 4;
}

