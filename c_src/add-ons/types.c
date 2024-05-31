#include "../../headers/types.h"
#include <stdio.h>
/*
Risc-V instruction types interface
*/

void R_Type(CMD cmd, char* rd, char* funct3, char* rs1, char* rs2, char* funct7)
{
    /*
    R_Type: Extracts the fields for an R-type instruction.
    cmd - the instruction command as an unsigned integer.
    rd - pointer to store the destination register.
    funct3 - pointer to store the funct3 field.
    rs1 - pointer to store the first source register.
    rs2 - pointer to store the second source register.
    funct7 - pointer to store the funct7 field.
    return: void
    */
    *rs1 = get_rs1(cmd);
    *rd = get_rd(cmd);
    *rs2 = get_rs2(cmd);
    *funct3 = get_funct3(cmd);
    *funct7 = get_funct7(cmd);
}

void I_Type(CMD cmd, char* funct3, char* rs1, char* rd, short* imm)
{
    /*
    I_Type: Extracts the fields for an I-type instruction.
    cmd - the instruction command as an unsigned integer.
    funct3 - pointer to store the funct3 field.
    rs1 - pointer to store the source register.
    rd - pointer to store the destination register.
    imm - pointer to store the immediate value.
    return: void
    */
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

void S_Type(CMD cmd, char* funct3, char* rs1, char* rs2, short* imm)
{
    /*
    S_Type: Extracts the fields for an S-type instruction.
    cmd - the instruction command as an unsigned integer.
    funct3 - pointer to store the funct3 field.
    rs1 - pointer to store the first source register.
    rs2 - pointer to store the second source register.
    imm - pointer to store the immediate value.
    return: void
    */
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

void B_Type(CMD cmd, char* funct3, char* rs1, short* imm, char* rs2)
{
    /*
    B_Type: Extracts the fields for a B-type instruction.
    cmd - the instruction command as an unsigned integer.
    funct3 - pointer to store the funct3 field.
    rs1 - pointer to store the first source register.
    imm - pointer to store the immediate value.
    rs2 - pointer to store the second source register.
    return: void
    */
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

void U_Type(CMD cmd, char* rd, int* imm)
{
    /*
    U_Type: Extracts the fields for a U-type instruction.
    cmd - the instruction command as an unsigned integer.
    rd - pointer to store the destination register.
    imm - pointer to store the immediate value.
    return: void
    */
    *rd = get_rd(cmd);
    *imm = (cmd >> 12) & get_n(20);
}
