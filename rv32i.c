#include "cpu.h"

char LUI(int cmd, State* state) // load upper immediate
{
    char rd = get_rd(command);
    int imm = (command >> 12) & get_n(20);
    state->general_purpose[rd] = imm;
    return 1;
}

char AUIPC(int cmd, State* state) // add upper immediate to PC
{
    char rd = get_rd(command);
    int imm = (command >> 12) & get_n(20);
    state->general_purpose[rd] = state->pc + imm ;
    return 1;
}

char JAL(int cmd, State* state) // jump and link
{
    char rd = get_rd(command);
    int imm = (command >> 12) & get_n(11);
    state->pc += imm;
    state->general_purpose[rd] = state->pc + 4;
    state->pc -= 4;
    return 1;
}

char JALR(int cmd, State* state) // jump and link register
{
    char rd = get_rd(command);
    short imm = (command >> 20) & get_n(11);
    char rs1 = (command >> 15) & RD;
    state->general_purpose[rs1] += imm;
    state->pc = state->general_purpose[rs1] ^ 1;
    state->general_purpose[rd] = state->pc;
    state->pc -= 4;
    return 1;
}

char CJUMPS(int cmd, State* state) //conditional jumps
{
    char funct3 = (cmd >> 12) & get_n(3);
    char rd = get_rd(cmd);
    char rs1 = get_rs1(cmd);
    short imm = ((cmd >> 31) & 1) << 11;
    imm |= ((cmd >> 7) & 1) << 1;
    imm |= ((cmd >> 25) & get_n(6)) << 5;
    imm |= ((cmd >> 8) & get_n(4)) << 11;
    char rs2 = get_rs2(cmd);
    state->pc -= 4;
    switch (funct3) {
    case 0b000: // BEQ
        if (state->general_purpose[rs1] == state->general_purpose[rs2]) {
            state->pc += imm;
        }
        return 1;
    case 0b001: // BNE
        if (state->general_purpose[rs1] != state->general_purpose[rs2]) {
            state->pc += imm;
        }
        return 1;
    case 0b100: // BLT
        if (state->general_purpose[rs1] < state->general_purpose[rs2]) {
            state->pc += imm;
        }
        return 1;
    case 0b101: // BGE
        if (state->general_purpose[rs1] >= state->general_purpose[rs2]) {
            state->pc += imm;
        }
        return 1;
    case 0b110: // BLTU
    {
        unsigned char urs1 = (unsigned)state->general_purpose[rs1];
        unsigned char urs2 = (unsigned)state->general_purpose[rs2];
        if (urs1 < urs2) {
            state->pc += imm;
        }
        return 1;
    }
    case 0b111: // BGEU
    {
        unsigned char urs1 = (unsigned)state->general_purpose[rs1];
        unsigned char urs2 = (unsigned)state->general_purpose[rs2];
        if (urs1 >= urs2) {
            state->pc += imm;
        }
        return 1;
    }
    }
    return 0;
}

char STORE(int cmd, State* state) // store in memory
{
    char funct3 = get_funct3(cmd);
    char rs1 = get_rs1(cmd);
    char rs2 = get_rs2(cmd);
    short imm = (cmd >> 25) & get_n(7);
    imm <<=5;
    imm += (cmd << 7) & get_n(5);
    int base_address = rs1 + imm;
    switch (funct3)
    {
    case 0b000: //SB
        state->memory[base_address] = state->general_purpose[rs2];
        return 1;
    case 0b001: //SH
        short* ptr = (short*)(state->memory);
        ptr[base_address] = state->general_purpose[rs2];
        return 1;
    case 0b010: //SW
        int* ptr = (int*)(state->memory);
        ptr[base_address] = state->general_purpose[rs2];
        return 1;
    }
    return 0;
}

char LOAD(int cmd, State* state) // load from memory
{
    char funct3 = get_funct3(cmd);
    char rd = get_rd(cmd);
    char rs1 = get_rs1(cmd);
    short imm = (cmd >> 20) & get_n(11);
    int base_address = state->general_purpose[rs1] + imm;
    char sign = state->memory[base_address] & (1 << 7);

    switch (funct3) {
        case 0b000: // LB
            state->general_purpose[rd] = state->memory[base_address] & get_n(8);
            return 1;
        case 0b001: // LH
            state->general_purpose[rd] = state->memory[base_address] & get_n(16);
            return 1;
        case 0b010: // LW
            state->general_purpose[rd] = state->memory[base_address] & get_n(32);
            return 1;
        case 0b100: // LBU
            state->general_purpose[rd] = (sign << 23) + (state->memory[base_address] & get_n(8));
            return 1;
        case 0b101: // LHU
            state->general_purpose[rd] = (sign << 23) + (state->memory[base_address] & get_n(16));
            return 1;
    }
    return 0;
}

char ALU(int cmd, State* state) // arithmetic and logical operations
{
    char rs1 = get_rs1(cmd);
    char rd = get_rd(cmd);
    char rs2 = get_rs2(cmd);
    char funct3 = get_funct3(cmd);
    char funct7 = get_funct7(cmd);
    switch (funct3)
    {
    case 0b000:
        switch (funct7)
        {
        case 0b0000000: // ADD
            state->general_purpose[rd] = state->general_purpose[rs1] + state->general_purpose[rs2];
            return 1;
        case 0b0100000: // SUB
            state->general_purpose[rd] = state->general_purpose[rs1] - state->general_purpose[rs2];
            return 1;
        }
    case 0b001: // SLL
        state->general_purpose[rd] = (state->general_purpose[rs1] >> state->general_purpose[rs2]);
        return 1;
    case 0b010: // SLT
        state->general_purpose[rd] = state->general_purpose[rs1] < state->general_purpose[rs2];
        return 1;
    case 0b011: //SLTU
        state->general_purpose[rd] = (unsigned)state->general_purpose[rs1] < (unsigned)state->general_purpose[rs2];
        return 1;
    case 0b100: // XOR
        state->general_purpose[rd] = state->general_purpose[rs1] ^ state->general_purpose[rs2];
        return 1;
    case 0b101:
        switch (funct3)
        {
        case 0b0000000: //SRL
            state->general_purpose[rd] = (state->general_purpose[rs1] >> state->general_purpose[rs2]);
            return 1;
        case 0b0100000: //SRA
            int sign = (rs1 < 0) << 31;
            state->general_purpose[rd] = (state->general_purpose[rs1] >> state->general_purpose[rs2]) | sign;
            return 1;

        }
    case 0b110: //OR
        state->general_purpose[rd] = state->general_purpose[rs1] | state->general_purpose[rs2];
        return 1;
    case 0b111: //AND
        state->general_purpose[rd] = state->general_purpose[rs1] & state->general_purpose[rs2];
        return 1;
    }
    return 0;
}

char ALUI(int cmd, State* state) // immediate arithmetic and logical operations
{
    char funct3 = get_funct3(cmd);
    char rs1 = get_rs1(cmd);
    char rd = get_rd(cmd);
    short imm = (cmd >> 20) & get_n(11);
    // for logical shifts
    char shamt = imm & get_n(5);
    char funct7 = (imm >> 5) & get_n(7);
    switch (funct3)
    {
    case 0b000: //ADDI
        state->general_purpose[rd] = state->general_purpose[rs1] + imm;
        return 1;
    case 0b010: //SLTI
        state->general_purpose[rd] = state->general_purpose[rs1] < imm;
        return 1;;
    case 0b011: //SLTIU
        state->general_purpose[rd] = (unsigned)state->general_purpose[rs1] < (unsigned)imm;
        return 1;
    case 0b100: //XORI
        state->general_purpose[rd] = state->general_purpose[rs1] ^ imm;
        return 1;
    case 0b110: //ORI
        state->general_purpose[rd] = state->general_purpose[rs1] | imm;
        return 1;
    case 0b111: //ANDI
        state->general_purpose[rd] = state->general_purpose[rs1] & imm;
        return 1;
    case 0b001: //SLLI
        state->general_purpose[rd] = (state->general_purpose[rs1] << shamt);
        return 1;
    case 0b101: //SRLI or SRAI
        switch (funct7)
        {
        case 0b0000000: //SRLI
            state->general_purpose[rd] = (state->general_purpose[rs1] >> shamt);
            return 1;
        case 0b0100000: //SRAI
            int sign = (rs1 < 0) << 31;
            state->general_purpose[rd] = (state->general_purpose[rs1] >> shamt) | sign;
            return 1;
        }
    }
    return 0;
}


