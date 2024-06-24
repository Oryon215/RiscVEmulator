#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include "cpu.h"

typedef unsigned int CMD;

void R_Type(CMD cmd, char* rd, char* funct3, char* rs1, char* rs2, char* funct7);

void I_Type(CMD cmd, char* funct3, char* rs1, char* rd, short* imm);

void S_Type(CMD cmd, char* funct3, char* rs1, char* rs2, short* imm);

void B_Type(CMD cmd, char* funct3, char* rs1, short* imm, char* rs2);

void U_Type(CMD cmd, char* rd, int* imm);

#endif // TYPES_H_INCLUDED
