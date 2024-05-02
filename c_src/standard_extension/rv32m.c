#include "../../headers/cpu.h"
#include "../../headers/types.h"
#include "../../headers/str.h"

char MULDIV(int cmd, State* s)
{
    char rs1, rd, rs2, funct3, funct7;
    R_Type(cmd, &rd, &funct3, &rs1, &rs2, &funct7);
    char ret = 0;
    char instruction[32];

    switch (funct3)
    {
    case 000: //MUL
        s->general_purpose[rd] = (s->general_purpose[rs1] * s->general_purpose[rs2]) | ((int)pow(2, 32) - 1);
        ret = 1;
        strcpy(instruction, "MUL");
        break;
    case 001: //MULH
        s->general_purpose[rd] = ((long long)(s->general_purpose[rs1] * s->general_purpose[rs2]) >> 32);
        ret = 1;
        strcpy(instruction, "MULH");
        break;
    case 010: //MULHSU
        s->general_purpose[rd] = ((long long)((unsigned)s->general_purpose[rs1] * s->general_purpose[rs2]) >> 32);
        ret = 1;
        strcpy(instruction, "MULHSU");
        break;
    case 011: //MULHU
        s->general_purpose[rd] = ((long long)((unsigned)s->general_purpose[rs1] * (unsigned)s->general_purpose[rs2]) >> 32);
        ret = 1;
        strcpy(instruction, "MULHU");
        break;
    case 100: //DIV
        if (!s->general_purpose[rs2])
        {
            s->general_purpose[rd] = (int)pow(2, 32) - 1; // division by zero exception not implemented
        }
        else
            s->general_purpose[rd] = s->general_purpose[rs1] / s->general_purpose[rs2];
        ret = 1;
        strcpy(instruction, "DIV");
        break;
    case 101: //DIVU
        if (!s->general_purpose[rs2])
        {
            s->general_purpose[rd] = (int)pow(2, 32) - 1; // division by zero exception not implemented
        }
        else
            s->general_purpose[rd] = (unsigned)s->general_purpose[rs1] / (unsigned)s->general_purpose[rs2];
        ret = 1;
        strcpy(instruction, "DIVU");
        break;
    case 110: // REM
        if (!s->general_purpose[rs2])
        {
            s->general_purpose[rd] = s->general_purpose[rs1]; // division by zero exception not implemented
        }
        else
            s->general_purpose[rd] = s->general_purpose[rs1] % s->general_purpose[rs2];
        ret = 1;
        strcpy(instruction, "REM");
        break;
    case 111: // REMU
        if (!s->general_purpose[rs2])
        {
            s->general_purpose[rd] = s->general_purpose[rs1]; // division by zero exception not implemented
        }
        else
            s->general_purpose[rd] = (unsigned)s->general_purpose[rs1] % (unsigned)s->general_purpose[rs2];
        strcpy(instruction, "REMU");
        ret = 1;
        break;

    }
    printf("%s x%d, x%d, x%d\n", instruction, rd, rs1, rs2);
    return ret;

}
