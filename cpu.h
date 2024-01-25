#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct State {
    int general_purpose[32];
    unsigned int pc;
    unsigned char* memory;
} State;

int EmulateRiscV(State* state);

#define get_n(n) (int)(pow(2, n) - 1)
#define get_rd(cmd) ((cmd >> 7) & get_n(5))
#define get_funct3(cmd) ((cmd >> 12) & get_n(3))
#define get_funct7(cmd) ((cmd >> 25) & get_n(7))
#define get_rs1(cmd) ((cmd >> 15) & get_n(5))
#define get_rs2(cmd) ((cmd >> 20) & get_n(5))


//instruction functions
char LUI(int cmd, State* state);
char AUIPC(int cmd, State* state);
char JAL(int cmd, State* state);
char CJUMPS(int cmd, State* state);
char STORE(int cmd, State* state);
char LOAD(int cmd, State* state);
char ALU(int cmd, State* state);
char ALUI(int cmd, State* state);
#endif // CPU_H_INCLUDED
