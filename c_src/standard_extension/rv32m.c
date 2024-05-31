#include "../../headers/cpu.h"

char MULDIV(CMD cmd, State* s)
{
    /*
    Handle multiplication, division and modulo operations
    cmd - current instruction
    s - current program state
    return: 1 on success
    */
    char rs1, rd, rs2, funct3, funct7;
    R_Type(cmd, &rd, &funct3, &rs1, &rs2, &funct7);
    char ret = 0;
    char opcode[32];

    switch (funct3)
    {
    case 000: //MUL
        s->general_purpose[rd] = (s->general_purpose[rs1] * s->general_purpose[rs2]) | ((int)pow(2, 32) - 1);
        ret = 1;
        strcpy1(opcode, "MUL");
        break;
    case 001: //MULH
        s->general_purpose[rd] = ((long long)(s->general_purpose[rs1] * s->general_purpose[rs2]) >> 32);
        ret = 1;
        strcpy1(opcode, "MULH");
        break;
    case 010: //MULHSU
        s->general_purpose[rd] = ((long long)((unsigned)s->general_purpose[rs1] * s->general_purpose[rs2]) >> 32);
        ret = 1;
        strcpy1(opcode, "MULHSU");
        break;
    case 011: //MULHU
        s->general_purpose[rd] = ((long long)((unsigned)s->general_purpose[rs1] * (unsigned)s->general_purpose[rs2]) >> 32);
        ret = 1;
        strcpy1(opcode, "MULHU");
        break;
    case 100: //DIV
        if (!s->general_purpose[rs2])
        {
            s->general_purpose[rd] = (int)pow(2, 32) - 1; // division by zero exception not implemented
        }
        else
            s->general_purpose[rd] = s->general_purpose[rs1] / s->general_purpose[rs2];
        ret = 1;
        strcpy1(opcode, "DIV");
        break;
    case 101: //DIVU
        if (!s->general_purpose[rs2])
        {
            s->general_purpose[rd] = (int)pow(2, 32) - 1; // division by zero exception not implemented
        }
        else
            s->general_purpose[rd] = (unsigned)s->general_purpose[rs1] / (unsigned)s->general_purpose[rs2];
        ret = 1;
        strcpy1(opcode, "DIVU");
        break;
    case 110: // REM
        if (!s->general_purpose[rs2])
        {
            s->general_purpose[rd] = s->general_purpose[rs1]; // division by zero exception not implemented
        }
        else
            s->general_purpose[rd] = s->general_purpose[rs1] % s->general_purpose[rs2];
        ret = 1;
        strcpy1(opcode, "REM");
        break;
    case 111: // REMU
        if (!s->general_purpose[rs2])
        {
            s->general_purpose[rd] = s->general_purpose[rs1]; // division by zero exception not implemented
        }
        else
            s->general_purpose[rd] = (unsigned)s->general_purpose[rs1] % (unsigned)s->general_purpose[rs2];
        strcpy1(opcode, "REMU");
        ret = 1;
        break;

    }
    sprintf(instruction, "%s x%d, x%d, x%d\n", opcode, rd, rs1, rs2);
    return ret;

}
