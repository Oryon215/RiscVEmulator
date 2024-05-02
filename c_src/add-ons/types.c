#include "../../headers/types.h"
#include <stdio.h>

void R_Type(int cmd, char* rd, char* funct3, char* rs1, char* rs2, char* funct7)
{
    *rs1 = get_rs1(cmd);
    *rd = get_rd(cmd);
    *rs2 = get_rs2(cmd);
    *funct3 = get_funct3(cmd);
    *funct7 = get_funct7(cmd);
}

void I_Type(int cmd, char* funct3, char* rs1, char* rd, short* imm)
{
    *funct3 = get_funct3(cmd);
    *rs1 = get_rs1(cmd);
    *rd = get_rd(cmd);
    *imm = (cmd >> 20) & get_n(12);
    char sign = (*imm & ((short)pow(2, 11))) >> 11;
    if (sign == 1)
    {
        *imm |= (get_n(4) << 12);
    }
}

void S_Type(int cmd, char* funct3, char* rs1, char* rs2, short* imm)
{
    *funct3 = get_funct3(cmd);
    *rs1 = get_rs1(cmd);
    *rs2 = get_rs2(cmd);
    *imm = (cmd >> 25) & get_n(7);
    *imm <<=5;
    if ((*imm >> 11) & 1)
    {
        *imm |= get_n(20) << 12;
    }
    *imm |= (cmd >> 7) & get_n(5);
}

void B_Type(int cmd, char* funct3, char* rs1, short* imm, char* rs2)
{
    *funct3 = (cmd >> 12) & get_n(3);
    *rs1 = get_rs1(cmd);
    *imm = ((cmd >> 31) & get_n(1)) << 12;
    if ((*imm >> 12) & 1) // sign extend
    {
        *imm |= get_n(19) << 13;
    }
    *imm |= ((cmd >> 7) & get_n(1)) << 11;
    *imm |= ((cmd >> 25) & get_n(6)) << 5;
    *imm |= ((cmd >> 8) & get_n(4)) << 1;
    *rs2 = get_rs2(cmd);
}

void U_Type(int cmd, char* rd, int* imm)
{
    *rd = get_rd(cmd);
    *imm = (cmd >> 12) & get_n(20);
}
