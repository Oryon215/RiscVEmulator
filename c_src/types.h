#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include "cpu.h"

void R_Type(int cmd, char* rd, char* funct3, char* rs1, char* rs2, char* funct7);

void I_Type(int cmd, char* funct3, char* rs1, char* rd, short* imm);

void S_Type(int cmd, char* funct3, char* rs1, char* rs2, short* imm);

void B_Type(int cmd, char* funct3, char* rd, char* rs1, short* imm, char* rs2);

void U_Type(int cmd, char* rd, int* imm);

#endif // TYPES_H_INCLUDED
