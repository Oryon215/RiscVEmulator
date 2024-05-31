#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dlfcn.h>
#include "str.h"
#include "types.h"

#define MaxBreakpoints 10
typedef unsigned int CMD;
typedef unsigned int Address;

extern char instruction[60];

typedef struct Segment
{
    Address addr; // segment starting point
    unsigned int size; // segment size
    unsigned char permissions; // segment permissions
}Segment; // Manage Program Memory Segments

typedef struct State {
    int general_purpose[32]; // general purpose registers
    Address pc; // program counter
    unsigned char* memory; // program memory
    unsigned int memory_size; // program memory size
    Address base_address; // base address of program
    int csr[4096]; // control and status registers
    Segment* memory_segments; // memory segments of program
    unsigned int segment_count; // number of memory segments of program
    int* breakpoints[MaxBreakpoints]; // breakpoints
    int current_breakpoint; // number of breakpoints currently
    char* symtab; // symbol table
    unsigned int symtab_size; // size of symbol table
    char* strtab; // string table
    unsigned int strtab_size; // size of string table
} State;

int ChangeBit(unsigned int num, int args, ...);

int EmulateRiscV(State* state);
void UnimplementedInstruction(CMD cmd, State* state);
void PrintState(State* state);
// memory handling
char CheckOperation(State* s, char operation, Address addr, char exception);
#define R 2
#define W 1
#define X 0
#define in_range(a, b, c) (a <= b && b <= c)

#define get_n(n) (unsigned int)(pow(2, n) - 1)
#define get_rd(cmd) ((cmd >> 7) & get_n(5))
#define get_funct3(cmd) ((cmd >> 12) & get_n(3))
#define get_funct7(cmd) ((cmd >> 25) & get_n(7))
#define get_rs1(cmd) ((cmd >> 15) & get_n(5))
#define get_rs2(cmd) ((cmd >> 20) & get_n(5))

// general purpose listings
#define zero 0
#define ra 1
#define sp 2
#define gp 3
#define tp 4
#define t0 5
#define t1 6
#define t2 7
#define s0 8
#define s1 9
#define a0 10
#define a1 11
#define a2 12
#define a3 13
#define a4 14
#define a5 15
#define a6 16
#define a7 17
#define s2 18
#define s3 19
#define s4 20
#define s5 21
#define s6 22
#define s7 23
#define s8 24
#define s9 25
#define s10 26
#define s11 27
#define t3 28
#define t4 29
#define t5 30
#define t6 31


// CSR's listing
#define mvendorid 0xF11
#define marchid 0xF12
#define mimpid 0xF13
#define mhartid 0xF14

#define mstatus 0x300
#define misa 0x301
#define medeleg 0x302
#define mideleg 0x303
#define mie 0x304
#define mtvec 0x305

#define mstrach 0x340
#define mepc 0x341
#define mcause 0x342
#define mbadaddr 0x343
#define mip 0x344

#define sstatus 0x100
#define sedeleg 0x102
#define sideleg 0x103
#define sie 0x104
#define stvec 0x105

#define sscratch 0x140
#define sepc 0x141
#define scause 0x142
#define sbadaddr 0x343
#define sip 0x144



//instruction functions
//rv32i
char LUI(CMD cmd, State* state);
char AUIPC(CMD cmd, State* state);
char JAL(CMD cmd, State* state);
char JALR(CMD cmd, State* state);
char CJUMPS(CMD cmd, State* state);
char STORE(CMD cmd, State* state);
char LOAD(CMD cmd, State* state);
char ALU(CMD cmd, State* state);
char ALUI(CMD cmd, State* state);
//rv32m
char MULDIV(CMD cmd, State* s);
//rv32zicsr
char ZICSR(CMD cmd, State* s);
//exception handling
char ECALL(CMD cmd, State* s);
void RaiseInterrupt(State* s, unsigned char error_code);
void M_Catch(State* s, unsigned char error_code, unsigned char exception);
void MIVT(State* s, unsigned char error_code, unsigned char exception);
void SIVT(State* s, unsigned char error_code, unsigned char exception);

//syscall table
void Syscall_Table(State* s);

//plic
#define Mouse 1
#define Keyboard 2

#define GatewayCount 2
#define TargetCount 1

typedef struct Target
{
    State* s;
    unsigned char privilege;
    unsigned char IE[GatewayCount];
    int threshold;
} Target;

typedef struct Gateway
{
    int source_addr;
    int priority;
    int id;
    unsigned char IP; //interrupt pending
} Gateway;

extern Gateway** gateways;
extern Target** targets;

//hardware
unsigned char KeyboardPending();
unsigned char MousePending();

//loading
void* Load(State* s, char* filename, char* addonname);

//debugger
void Break(State* s, int b);
void CheckBreapoints(State* s);

//add-ons:
extern void (*InitAddOn)(State* s);
extern void (*AddOn)(State* s);

//Heap functions
void* MMAP(State* s, unsigned int addr, size_t length, int protect, int flags, int filedes, off_t offset);
int BRK(State* s, unsigned int addr);
int MUNMAP(State* s, unsigned int addr, size_t length);
void* AddMemory(State* s, char* st);
#endif // CPU_H_INCLUDED
