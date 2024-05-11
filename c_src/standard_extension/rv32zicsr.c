#include "../../headers/cpu.h"
#include "../../headers/types.h"
#include "../../headers/str.h"

char ZICSR(int cmd, State* s)
{
    char funct3, rs1, rd;
    short imm;
    I_Type(cmd, &funct3, &rs1, &rd, &imm);
    char ret = 0;
    char opcode[32];

    switch(funct3)
    {
    case 001: // CSRRW
        s->general_purpose[rd] = s->csr[imm];
        s->csr[imm] = s->general_purpose[rs1];
        ret = 1;
        strcpy(opcode, "CSRRW");
        break;
    case 010: //CSRRS
        s->general_purpose[rd] = s->csr[imm];
        s->csr[imm] |= s->csr[rs1];
        ret = 1;
        strcpy(opcode, "CSRRS");
        break;
    case 011: //CSRRC
        s->general_purpose[rd] = s->csr[imm];
        s->csr[imm] ^= s->csr[rs1];
        ret = 1;
        strcpy(opcode, "CSRRS");
        break;
    case 101: //CSRRWI
        s->general_purpose[rd] = s->csr[imm];
        s->csr[imm] ^= s->csr[imm];
        s->csr[imm] |= (unsigned)rs1;
        ret = 1;
        strcpy(opcode, "CSRRWI");
        break;
    case 110: //CSRRSI
        s->general_purpose[rd] = s->csr[imm];
        s->csr[imm] |= (unsigned)rs1;
        ret = 1;
        strcpy(opcode, "CSRRSI");
        break;
    case 111: //CSRRCI
        s->general_purpose[rd] = s->csr[imm];
        s->csr[imm] ^= (unsigned)rs1;
        ret = 1;
        strcpy(opcode, "CSRRCI");
        break;
    }
    sprintf(instruction, "%s %d, %d, csr - %d", opcode, rd, rs1, imm);
    return ret;
}
