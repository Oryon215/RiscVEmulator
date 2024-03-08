#include "cpu.h"
#include "types.h"
#include "str.h"

char LUI(int cmd, State* state) // load upper immediate
{
    char rd;
    int imm;
    U_Type(cmd, &rd, &imm);
    state->general_purpose[rd] = imm;
    printf("LUI %d %d\n", rd, imm);
    return 1;
}

char AUIPC(int cmd, State* state) // add upper immediate to PC
{
    char rd;
    int imm;
    U_Type(cmd, &rd, &imm);
    state->general_purpose[rd] = state->pc + imm ;
    printf("AUIPC %d, %d\n", rd, imm);
    return 1;
}

char JAL(int cmd, State* state) // jump and link
{
    char rd = get_rd(cmd);
    int imm = (cmd >> 31) & get_n(1);
    imm <<= 8;
    imm &= (cmd >> 12) & get_n(8);
    imm <<= 1;
    imm &= (cmd >> 20) & get_n(1);
    imm <<= 10;
    imm &= (cmd >> 21) & get_n(10);
    state->general_purpose[rd] = state->pc + 4;
    state->pc += imm;
    state->pc -= 4;
    printf("JAL %d, %d\n", rd, state->pc + 4);
    return 1;
}

char JALR(int cmd, State* state) // jump and link register
{
    char rd = get_rd(cmd);
    short imm = (cmd >> 20) & get_n(11);
    char rs1 = (cmd >> 15) & get_n(5);
    state->general_purpose[rd] = state->pc + 4;
    state->pc = (state->general_purpose[rs1] + imm) ;
    state->pc -= 4;
    printf("JALR %d, %d\n", rd, state->general_purpose[rs1] + imm);
    return 1;
}

char CJUMPS(int cmd, State* state) //conditional jumps
{
    char funct3, rd, rs1, rs2;
    short imm;
    B_Type(cmd, &funct3, &rd, &rs1, &imm, &rs2);
    state->pc -= 4;
    char ret = 0;
    char instruction[32];
    switch (funct3) {
    case 0b000: // BEQ
        if (state->general_purpose[rs1] == state->general_purpose[rs2]) {
            state->pc += imm;
        }
        strcpy(instruction, "BEQ");
        ret = 1;
        break;
    case 0b001: // BNE
        if (state->general_purpose[rs1] != state->general_purpose[rs2]) {
            state->pc += imm;
        }
        strcpy(instruction, "BNE");
        ret = 1;
        break;
    case 0b100: // BLT
        if (state->general_purpose[rs1] < state->general_purpose[rs2]) {
            state->pc += imm;
        }
        strcpy(instruction, "BLT");
        ret = 1;
        break;
    case 0b101: // BGE
        if (state->general_purpose[rs1] >= state->general_purpose[rs2]) {
            state->pc += imm;
        }
        strcpy(instruction, "BGE");
        ret = 1;
        break;
    case 0b110: // BLTU
    {
        unsigned char urs1 = (unsigned)state->general_purpose[rs1];
        unsigned char urs2 = (unsigned)state->general_purpose[rs2];
        if (urs1 < urs2) {
            state->pc += imm;
        }
        strcpy(instruction, "BLTU");
        ret = 1;
        break;
    }
    case 0b111: // BGEU
    {
        unsigned char urs1 = (unsigned)state->general_purpose[rs1];
        unsigned char urs2 = (unsigned)state->general_purpose[rs2];
        if (urs1 >= urs2) {
            state->pc += imm;
        }
        strcpy(instruction, "BGEU");
        ret = 1;
        break;
    }
    }
    return ret;
}

char STORE(int cmd, State* state) // store in memory
{
    char funct3, rs1, rs2;
    short imm;
    S_Type(cmd, &funct3, &rs1, &rs2, &imm);
    int base_address = rs1 + imm;
    char ret = 0;
    char instruction[32];
    switch (funct3)
    {
    case 0b000: //SB
        strcpy(instruction, "SB");
        state->memory[base_address] = state->general_purpose[rs2];
        ret = 1;
        break;
    case 0b001: ;//SH
        strcpy(instruction, "SH");
        short* ptr1 = (short*)(state->memory);
        ptr1[base_address] = state->general_purpose[rs2];
        ret = 1;
        break;
    case 0b010: ;//SW
        strcpy(instruction, "SW");
        int* ptr2 = (int*)(state->memory);
        ptr2[base_address] = state->general_purpose[rs2];
        ret = 1;
        break;
    }
    printf("%s %d %d\n", instruction, base_address, rs2);
    return ret;
}

char LOAD(int cmd, State* state) // load from memory
{
    char funct3, rd, rs1;
    short imm;
    I_Type(cmd, &funct3, &rs1, &rd, &imm);
    int base_address = state->general_purpose[rs1] + imm;
    char sign = state->memory[base_address] & (1 << 7);
    char ret = 0;
    char instruction[32];

    switch (funct3) {
        case 0b000: // LB
            strcpy(instruction, "LB");
            state->general_purpose[rd] = state->memory[base_address] & get_n(8);
            ret = 1;
            break;
        case 0b001: // LH
            strcpy(instruction, "LH");
            state->general_purpose[rd] = state->memory[base_address] & get_n(16);
            ret = 1;
            break;
        case 0b010: // LW
            strcpy(instruction, "LW");
            state->general_purpose[rd] = state->memory[base_address] & get_n(32);
            ret = 1;
            break;
        case 0b100: // LBU
            strcpy(instruction, "LBU");
            state->general_purpose[rd] = (sign << 23) | (state->memory[base_address] & get_n(8));
            ret = 1;
            break;
        case 0b101: // LHU
            strcpy(instruction, "LHU");
            state->general_purpose[rd] = (sign << 23) | (state->memory[base_address] & get_n(16));
            ret = 1;
            break;
    }
    printf("%s %d, %d\n", instruction, rd, base_address);
    return ret;
}

char ALU(int cmd, State* state) // arithmetic and logical operations
{
    char rs1, rd, rs2, funct3, funct7;
    R_Type(cmd, &rd, &funct3, &rs1, &rs2, &funct7);
    char ret = 0;
    char instruction[32];
    switch (funct3)
    {
    case 0b000:
        switch (funct7)
        {
        case 0b0000000: // ADD
            strcpy(instruction, "ADD");
            state->general_purpose[rd] = state->general_purpose[rs1] + state->general_purpose[rs2];
            ret = 1;
            break;
        case 0b0100000: // SUB
            strcpy(instruction, "SUB");
            state->general_purpose[rd] = state->general_purpose[rs1] - state->general_purpose[rs2];
            ret = 1;
            break;
        }
        break;
    case 0b001: // SLL
        strcpy(instruction, "SLL");
        state->general_purpose[rd] = (state->general_purpose[rs1] >> state->general_purpose[rs2]);
        ret = 1;
        break;
    case 0b010: // SLT
        strcpy(instruction, "SLT");
        state->general_purpose[rd] = state->general_purpose[rs1] < state->general_purpose[rs2];
        ret = 1;
        break;
    case 0b011: //SLTU
        strcpy(instruction, "SLTU");
        state->general_purpose[rd] = (unsigned)state->general_purpose[rs1] < (unsigned)state->general_purpose[rs2];
        ret = 1;
        break;
    case 0b100: // XOR
        strcpy(instruction, "XOR");
        state->general_purpose[rd] = state->general_purpose[rs1] ^ state->general_purpose[rs2];
        ret = 1;
        break;
    case 0b101:
        switch (funct7)
        {
        case 0b0000000: //SRL
            strcpy(instruction, "SRL");
            state->general_purpose[rd] = (state->general_purpose[rs1] >> state->general_purpose[rs2]);
            ret = 1;
            break;
        case 0b0100000: ;//SRA
            strcpy(instruction, "SRA");
            int sign = (rs1 < 0) << 31;
            state->general_purpose[rd] = (state->general_purpose[rs1] >> state->general_purpose[rs2]) | sign;
            ret = 1;
            break;

        }
        break;
    case 0b110: //OR
        strcpy(instruction, "OR");
        state->general_purpose[rd] = state->general_purpose[rs1] | state->general_purpose[rs2];
        ret = 1;
        break;
    case 0b111: //AND
        strcpy(instruction, "AND");
        state->general_purpose[rd] = state->general_purpose[rs1] & state->general_purpose[rs2];
        ret = 1;
        break;
    }
    printf("%s x%d, x%d, x%d\n", instruction, rd, rs1, rs2);
    return ret;
}

char ALUI(int cmd, State* state) // immediate arithmetic and logical operations
{
    char funct3, rs1, rd;
    short imm;
    I_Type(cmd, &funct3, &rs1, &rd, &imm);
    char ret = 0;
    char funct7 = get_funct7(cmd);
    char shamt = imm & get_n(5);
    char instruction[32];
    switch (funct3)
    {
    case 0b000: //ADDI
        strcpy(instruction, "ADDI");
        state->general_purpose[rd] = state->general_purpose[rs1] + imm;
        ret = 1;
        break;
    case 0b010: //SLTI
        strcpy(instruction, "SLTI");
        state->general_purpose[rd] = state->general_purpose[rs1] < imm;
        ret = 1;
        break;
    case 0b011: //SLTIU
        strcpy(instruction, "SLTIU");
        state->general_purpose[rd] = (unsigned)state->general_purpose[rs1] < (unsigned)imm;
        ret = 1;
        break;
    case 0b100: //XORI
        strcpy(instruction, "XORI");
        state->general_purpose[rd] = state->general_purpose[rs1] ^ imm;
        ret = 1;
        break;

    case 0b110: //ORI
        strcpy(instruction, "ORI");
        state->general_purpose[rd] = state->general_purpose[rs1] | imm;
        ret = 1;
        break;
    case 0b111: //ANDI
        strcpy(instruction, "ANDI");
        state->general_purpose[rd] = state->general_purpose[rs1] & imm;
        ret = 1;
        break;
    case 0b001: //SLLI
        strcpy(instruction, "SLLI");
        state->general_purpose[rd] = (state->general_purpose[rs1] << shamt);
        ret = 1;
        break;
    case 0b101: //SRLI or SRAI
        switch (funct7)
        {
        case 0b0000000: ;//SRLI
            strcpy(instruction, "SRLI");
            state->general_purpose[rd] = (state->general_purpose[rs1] >> shamt);
            ret = 1;
            break;
        case 0b0100000: ;//SRAI
            strcpy(instruction, "SRAI");
            int sign = (rs1 < 0) << 31;
            state->general_purpose[rd] = (state->general_purpose[rs1] >> shamt) | sign;
            ret = 1;
            break;
        }
    }
    printf("%s x%d, x%d, %d\n", instruction, rd, rs1, imm);
    return ret;
}

char ECALL(State* state)
{
    return '0x0';
}


