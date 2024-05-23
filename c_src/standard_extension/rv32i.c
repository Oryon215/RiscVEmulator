#include "../../headers/cpu.h"

char LUI(int cmd, State* s) // load upper immediate
{
    char rd;
    int imm;
    U_Type(cmd, &rd, &imm);
    s->general_purpose[rd] = (imm << 12);
    sprintf(instruction, "LUI x%d %d\n", rd, imm);
    return 1;
}

char AUIPC(int cmd, State* s) // add upper immediate to PC
{
    char rd;
    int imm;
    U_Type(cmd, &rd, &imm);
    s->general_purpose[rd] = s->pc + (imm << 12);
    sprintf(instruction, "AUIPC x%d, %d\n", rd, imm);
    return 1;
}

char JAL(int cmd, State* s) // jump and link
{
    char rd = get_rd(cmd);
    char sign;
    int imm = (cmd >> 31) & get_n(1);
    sign = (imm & get_n(1));
    imm <<= 8;
    imm |= (cmd >> 12) & get_n(8);
    imm <<= 1;
    imm |= (cmd >> 20) & get_n(1);
    imm <<= 10;
    imm |= (cmd >> 21) & get_n(10);
    imm <<= 1;
    if (sign)
        imm |= get_n(12) << 20;
    if (imm % 4 != 0)
    {
        M_Catch(s, 0, 1);
    }
    s->general_purpose[rd] = s->pc + 4;
    s->pc += imm;
    s->pc -= 4; // it will be added later
    sprintf(instruction, "JAL x%d, %d\n", rd, imm);
    return 1;
}

char JALR(int cmd, State* s) // jump and link register
{
    char rd = get_rd(cmd);
    short imm = (cmd >> 20) & get_n(12);
    char sign = (imm >> 11) & 1;
    if (sign)
    {
        imm |= get_n(20) << 12;
    }
    char rs1 = (cmd >> 15) & get_n(5);
    if (imm % 4 != 0)
    {
        M_Catch(s, 0, 1);
    }
    s->general_purpose[rd] = s->pc + 4;
    s->pc = ((s->general_purpose[rs1] + imm) >> 1) << 1;
    s->pc -= 4;
    sprintf(instruction, "JALR x%d, x%d, %d\n", rd, rs1, imm);
    return 1;
}

char CJUMPS(int cmd, State* s) //conditional jumps
{
    char funct3, rs1, rs2;
    short imm;
    B_Type(cmd, &funct3, &rs1, &imm, &rs2);
    if (imm % 4 != 0)
    {
        M_Catch(s, 0, 1);
    }
    char ret = 0;
    char opcode[32];
    switch (funct3) {
    case 0b000: // BEQ
        if (s->general_purpose[rs1] == s->general_purpose[rs2]) {
            s->pc += imm;
            s->pc -= 4;
        }
        strcpy1(opcode, "BEQ");
        ret = 1;
        break;
    case 0b001: // BNE
        if (s->general_purpose[rs1] != s->general_purpose[rs2]) {
            s->pc += imm;
            s->pc -= 4;
        }
        strcpy1(opcode, "BNE");
        ret = 1;
        break;
    case 0b100: // BLT
        if (s->general_purpose[rs1] < s->general_purpose[rs2]) {
            s->pc += imm;
            s->pc -= 4;
        }
        strcpy1(opcode, "BLT");
        ret = 1;
        break;
    case 0b101: // BGE
        if (s->general_purpose[rs1] >= s->general_purpose[rs2]) {
            s->pc += imm;
            s->pc -= 4;
        }
        strcpy1(opcode, "BGE");
        ret = 1;
        break;
    case 0b110: // BLTU
    {
        unsigned char urs1 = (unsigned)s->general_purpose[rs1];
        unsigned char urs2 = (unsigned)s->general_purpose[rs2];
        if (urs1 < urs2) {
            s->pc += imm;
            s->pc -= 4;
        }
        strcpy1(opcode, "BLTU");
        ret = 1;
        break;
    }
    case 0b111: // BGEU
    {
        unsigned char urs1 = (unsigned)s->general_purpose[rs1];
        unsigned char urs2 = (unsigned)s->general_purpose[rs2];
        if (urs1 >= urs2) {
            s->pc += imm;
            s->pc -= 4;
        }
        strcpy1(opcode, "BGEU");
        ret = 1;
        break;
    }
    }
    sprintf(instruction, "%s x%d, x%d, %d\n", opcode, rs1, rs2, imm);
    return ret;
}

char STORE(int cmd, State* s) // store in memory
{
    char funct3, rs1, rs2;
    short imm;
    S_Type(cmd, &funct3, &rs1, &rs2, &imm);
    int address = s->general_purpose[rs1] + imm;
    char ret = 0;
    char opcode[32];
    CheckOperation(s, W, address, 1);
    switch (funct3)
    {
    case 0b000: //SB
        strcpy1(opcode, "SB");
        s->memory[address] = s->general_purpose[rs2];
        ret = 1;
        break;
    case 0b001: ;//SH
        strcpy1(opcode, "SH");
        short* ptr1 = (short*)(s->memory + address);
        ptr1 = s->general_purpose[rs2];
        ret = 1;
        break;
    case 0b010: ;//SW
        strcpy1(opcode, "SW");
        int* ptr2 = (int*)(s->memory + address);
        *ptr2 = s->general_purpose[rs2];
        ret = 1;
        break;
    }
    sprintf(instruction, "%s x%d %d(x%d)\n", opcode, rs2, imm, rs1);
    return ret;
}

char LOAD(int cmd, State* s) // load from memory
{
    char funct3, rd, rs1;
    short imm;
    I_Type(cmd, &funct3, &rs1, &rd, &imm);
    int address = s->general_purpose[rs1] + imm;
    char ret = 0;
    char opcode[32];
    CheckOperation(s, R, address, 1);
    switch (funct3) {
        case 0b000: // LB
            strcpy1(opcode, "LB");
            s->general_purpose[rd] = s->memory[address];
            if ((s->memory[address] >> 7) & 1)
            {
                s->general_purpose[rd] |= get_n(24) << 8;
            }
            ret = 1;
            break;
        case 0b001: // LH
            strcpy1(opcode, "LH");
            short* ptr1 = s->memory + address;
            s->general_purpose[rd] = *ptr1;
            if ((*ptr1 >> 15) & 1)
            {
                s->general_purpose[rd] |= get_n(16) << 16;
            }
            ret = 1;
            break;
        case 0b010: // LW
            strcpy1(opcode, "LW");
            int* ptr2 = s->memory + address;
            s->general_purpose[rd] = *ptr2;
            ret = 1;
            break;
        case 0b100: // LBU
            strcpy1(opcode, "LBU");
            s->general_purpose[rd] = s->memory[address];
            ret = 1;
            break;
        case 0b101: // LHU
            strcpy1(opcode, "LHU");
            short* ptr3 = s->memory + address;
            s->general_purpose[rd] = *ptr3;
            ret = 1;
            break;
    }
    sprintf(instruction, "%s x%d, %d(x%d)\n", opcode, rd, imm, rs1);
    return ret;
}

char ALU(int cmd, State* s) // arithmetic and logical operations
{
    char rs1, rd, rs2, funct3, funct7;
    R_Type(cmd, &rd, &funct3, &rs1, &rs2, &funct7);
    char ret = 0;
    char opcode[32];
    switch (funct3)
    {
    case 0b000:
        switch (funct7)
        {
        case 0b0000000: // ADD
            strcpy1(opcode, "ADD");
            s->general_purpose[rd] = s->general_purpose[rs1] + s->general_purpose[rs2];
            ret = 1;
            break;
        case 0b0100000: // SUB
            strcpy1(opcode, "SUB");
            s->general_purpose[rd] = s->general_purpose[rs1] - s->general_purpose[rs2];
            ret = 1;
            break;
        }
        break;
    case 0b001: // SLL
        strcpy1(opcode, "SLL");
        s->general_purpose[rd] = (s->general_purpose[rs1] << s->general_purpose[rs2]);
        ret = 1;
        break;
    case 0b010: // SLT
        strcpy1(opcode, "SLT");
        s->general_purpose[rd] = s->general_purpose[rs1] < s->general_purpose[rs2];
        ret = 1;
        break;
    case 0b011: //SLTU
        strcpy1(opcode, "SLTU");
        s->general_purpose[rd] = (unsigned)s->general_purpose[rs1] < (unsigned)s->general_purpose[rs2];
        ret = 1;
        break;
    case 0b100: // XOR
        strcpy1(opcode, "XOR");
        s->general_purpose[rd] = s->general_purpose[rs1] ^ s->general_purpose[rs2];
        ret = 1;
        break;
    case 0b101:
        switch (funct7)
        {
        case 0b0000000: //SRL
            strcpy1(opcode, "SRL");
            s->general_purpose[rd] = (s->general_purpose[rs1] >> s->general_purpose[rs2]);
            ret = 1;
            break;
        case 0b0100000: ;//SRA
            strcpy1(opcode, "SRA");
            int sign = 0;
            if (s->general_purpose[rs1] < 0)
            {
                sign = get_n(s->general_purpose[rs2]) << (32 - s->general_purpose[rs2]);
            }
            s->general_purpose[rd] = (s->general_purpose[rs1] >> s->general_purpose[rs2]) | sign;
            ret = 1;
            break;

        }
        break;
    case 0b110: //OR
        strcpy1(opcode, "OR");
        s->general_purpose[rd] = s->general_purpose[rs1] | s->general_purpose[rs2];
        ret = 1;
        break;
    case 0b111: //AND
        strcpy1(opcode, "AND");
        s->general_purpose[rd] = s->general_purpose[rs1] & s->general_purpose[rs2];
        ret = 1;
        break;
    }
    sprintf(instruction, "%s x%d, x%d, x%d\n", opcode, rd, rs1, rs2);
    return ret;
}

char ALUI(int cmd, State* s) // immediate arithmetic and logical operations
{
    char funct3, rs1, rd;
    short imm;
    I_Type(cmd, &funct3, &rs1, &rd, &imm);
    char ret = 0;
    char funct7 = get_funct7(cmd);
    char shamt = imm & get_n(5);
    char opcode[32];
    switch (funct3)
    {
    case 0b000: //ADDI
        strcpy1(opcode, "ADDI");
        s->general_purpose[rd] = s->general_purpose[rs1] + imm;
        ret = 1;
        break;
    case 0b010: //SLTI
        strcpy1(opcode, "SLTI");
        s->general_purpose[rd] = s->general_purpose[rs1] < imm;
        ret = 1;
        break;
    case 0b011: //SLTIU
        strcpy1(opcode, "SLTIU");
        s->general_purpose[rd] = (unsigned)s->general_purpose[rs1] < (unsigned)imm;
        ret = 1;
        break;
    case 0b100: //XORI
        strcpy1(opcode, "XORI");
        s->general_purpose[rd] = s->general_purpose[rs1] ^ imm;
        ret = 1;
        break;

    case 0b110: //ORI
        strcpy1(opcode, "ORI");
        s->general_purpose[rd] = s->general_purpose[rs1] | imm;
        ret = 1;
        break;
    case 0b111: //ANDI
        strcpy1(opcode, "ANDI");
        s->general_purpose[rd] = s->general_purpose[rs1] & imm;
        ret = 1;
        break;
    case 0b001: //SLLI
        imm = shamt;
        strcpy1(opcode, "SLLI");
        s->general_purpose[rd] = (s->general_purpose[rs1] << shamt);
        ret = 1;
        break;
    case 0b101: //SRLI or SRAI
        imm = shamt;
        switch (funct7)
        {
        case 0b0000000: ;//SRLI
            strcpy1(opcode, "SRLI");
            s->general_purpose[rd] = (s->general_purpose[rs1] >> shamt);
            ret = 1;
            break;
        case 0b0100000: ;//SRAI
            strcpy1(opcode, "SRAI");
            int sign = 0;
            if (s->general_purpose[rs1] < 0)
            {
                sign = get_n(shamt) << (32 - shamt);
            }
            s->general_purpose[rd] = (s->general_purpose[rs1] >> shamt) | sign;
            ret = 1;
            break;
        }
    }
    sprintf(instruction, "%s x%d, x%d, %d\n", opcode, rd, rs1, imm);
    return ret;
}



