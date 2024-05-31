#include "../../headers/cpu.h"
#define able 1
#define unable 0
#define A 0
#define V 1

/*
Memory leak detector
*/


typedef unsigned short U16;
typedef unsigned char U8;
int syscall_params[] = {1, 1, 1, 1, 1, 5, 5, 5, 4, 4,
4, 3, 3, 3, 2, 2, 2, 0, 2, 2, 1,
4, 5, 1, 3, 3, 1, 3, 2, 3, 2, 2,
2, 4, 3, 3, 3, 3, 4, 2, 2, 2, 0,
3, 3, 2, 2, 4, 4, 1, 1, 1, 2, 4,
5, 3, 3, 0, 2, 4, 3, 5, 3, 3, 3,
3, 4, 4, 4, 4, 4, 3, 4, 4, 4, 4,
4, 2, 1, 1, 4, 2, 4, 2, 4, 1, 2,
2, 1, 1, 4, 1, 1, 6, 2, 2, 3, 4,
3, 2, 3, 2, 2, 2, 4, 3, 4, 2, 3,
1, 2, 3, 3, 0, 1, 1, 2, 2, 2, 3,
1, 3, 2, 4, 2, 1, 2, 1, 3, 3, 3,
3, 1, 1, 1, 2, 1, 1, 0, 2, 2, 2,
2, 2, 2, 2, 1, 5, 3, 2, 2, 1, 0,
0, 0, 0, 0, 0, 0, 1, 2, 5, 4, 3,
4, 4, 3, 3, 1, 3, 4, 2, 3, 3, 3,
3, 6, 6, 5, 5, 2, 3, 3, 3, 1, 2,
2, 1, 4, 4, 4, 2, 5, 5, 3, 2, 1,
2, 4, 6, 6, 5, 3, 2, 6, 5, 5, 5}; // number of parameters per syscall

typedef struct {
U8 abits[8192];
U8 vbits[65536];
} SM; // secondary map

static SM* PM[65536]; // primary map

static SM* DSM; // de-initialized secondary map
static State* shadow; // shadow value state

void RecordAccess(Address address, unsigned char type)
{
    /*
    record wrong memory access
    address - memory address
    type - type of access
    return: void
    */
    char type_string[16];
    switch (type)
    {
        case V:
            strcpy1(type_string, "validity");
            break;
        case A:
            strcpy1(type_string, "accessability");
            break;
    }
    printf("Memory leak of type %s has occurred at %x\n", type_string, address);

}

SM* CopySM(SM* sm)
{
    /*
    copy SM contents to new ptr
    sm - secondary map
    return: ptr to new SM
    */
    SM* new_sm = (SM*)malloc(sizeof(SM));
    for (int i = 0; i < 8192; i++)
    {
        new_sm->abits[i] = sm->abits[i];
    }
    for (int i = 0; i < 65536; i++)
    {
        new_sm->vbits[i] = sm->vbits[i];
    }
    return new_sm;
}

SM* GetSMForReading(Address a)
{
    /*
    return SM by address for reading
    a - address
    return: ptr to SM in address
    */
    return PM[a >> 16];
}

SM* GetSMForWriting(Address a)
{
    /*
    return SM by address for writing
    a - address
    return: ptr to SM in address
    */
    SM** sm = PM + (a >> 16);
    if (*sm == DSM)
    {
        *sm = CopySM(DSM);
    }
    return *sm;
}

void GetBits(Address a, U8* abits, U8* vbits)
{
    /*
    return a bits and v bits to out parameters by address
    a - address
    return: void
    */
    SM* sm = GetSMForReading(a);
    U16 addr = a & get_n(16);
    U16 abits_addr = addr >> 3;
    U8 shift = addr & get_n(3);
    *abits = 1 & (sm->abits[abits_addr] >> shift);
    *vbits = sm->vbits[addr];
}

void SetBits(Addvress a, U8 abits, U8 vbits)
{
    /*
    set v and a bits by address
    a - address
    return: void
    */
    SM* sm = GetSMForWriting(a);
    U16 addr = a & get_n(16);
    U8 abits_addr = addr >> 3;
    U8 shift = addr & get_n(3);
    sm->abits[abits_addr] ^= (abits ^ 1) << shift;
    sm->vbits[addr] = vbits;
}

unsigned int LoadVN(Address a, int nbits)
{
    /*
    load N v-bits in address
    a - address
    nbits - number of v bits
    return: N V-bits
    */
    int i; unsigned int bits;
    for (int i = 0; i < nbits / 8; i++)
    {
        U8 vbits, abits;
        GetBits(a + i, &abits, &vbits);
        if (!abits)
        {
            RecordAccess(a + i, A);
        }
        bits <<= 8;
        bits |= vbits;
    }
    return bits;
}

void SetSegmentVBits(State* s)
{
    /*
    turn on segment v-bits
    s - state
    return: void
    */
    int i, j;
    for (i = 0; i < s->segment_count; i++)
    {
        for (j = 0; j < s->memory_segments[i].size; j++)
        {
            SetBits(s->memory_segments[i].addr + j, get_n(8), get_n(8));
        }
    }
}

void init_add_on(State* s)
{
    /*
    initialize add on
    s - state
    return: void
    */
    printf("ADD ON MEMCHECK INITIALIZED.\n");
    DSM = (SM*)malloc(sizeof(SM));
    shadow = (State*)malloc(sizeof(State));
   //init distinguished secondary map
   for (int i = 0; i < 8192; i++)
   {
       DSM->abits[i] = get_n(8);
   }
   for (int i = 0; i < 65536; i++)
   {
       PM[i] = DSM;
   }
   for (int i = 0; i < 32; i++)
   {
        shadow->general_purpose[i] = 0;
   }
   shadow->general_purpose[0] = get_n(32);
   shadow->pc = get_n(32);
   shadow->general_purpose[sp] = get_n(32);
   shadow->general_purpose[s0] = get_n(32);
   SetSegmentVBits(s);
}

void HandleEcall(State* s)
{
    /*
    handle environment call
    s - state
    return: void
    */
    if (shadow->general_purpose[a7] != get_n(32))
    {
        shadow->general_purpose[a7] = get_n(32);
        RecordAccess(s->pc, V);
        return;
    }
    int i;
    for (i = 0; i < syscall_params[s->general_purpose[a7]]; i++)
    {
        if (shadow->general_purpose[a0 + i] != get_n(32))
        {
            shadow->general_purpose[a0 + i] = get_n(32);
            RecordAccess(s->pc, V);
            return;
        }
    }
}


void HandleALU(State* s, CMD cmd)
{
    /*
    handle arithmetic and logical operations
    s - current state
    cmd - current instruction
    return: void
    */
    char rs1, rd, rs2, funct3, funct7;
    R_Type(cmd, &rd, &funct3, &rs1, &rs2, &funct7);
    switch (funct3)
    {
    case 0b000: //ADD
        shadow->general_purpose[rd] = shadow->general_purpose[rs1] & shadow->general_purpose[rs2];
        break;
    case 0b001: // SLL
        if (shadow->general_purpose[rs2] != get_n(32))
        {
            shadow->general_purpose[rd] = 0;
        }
        else
            shadow->general_purpose[rd] = (shadow->general_purpose[rs1] << s->general_purpose[rs2]) | get_n(s->general_purpose[rs2]);
        break;
    case 0b010: // SLT
        if (shadow->general_purpose[rs1] != get_n(32) || shadow->general_purpose[rs2] != get_n(32))
        {
            shadow->general_purpose[rd] = 0;
        }
        else
            shadow->general_purpose[rd] = get_n(32);
        break;
    case 0b011: //SLTU
        if (shadow->general_purpose[rs1] != get_n(32) || shadow->general_purpose[rs2] != get_n(32))
        {
            shadow->general_purpose[rd] = 0;
        }
        else
            shadow->general_purpose[rd] = get_n(32);
        break;
    case 0b100: // XOR
        shadow->general_purpose[rd] = shadow->general_purpose[rs1] & shadow->general_purpose[rs2];
        break;
    case 0b101:
        switch (funct7)
        {
        case 0b0000000: //SRL
            if (shadow->general_purpose[rs2] != get_n(32))
            {
                shadow->general_purpose[rd] = 0;
            }
            else
                shadow->general_purpose[rd] = (shadow->general_purpose[rs1] >> s->general_purpose[rs2]);
            break;
        case 0b0100000: ;//SRA
            if (shadow->general_purpose[rs2] != get_n(32))
            {
                shadow->general_purpose[rd] = 0;
            }
            else
            {
                if (s->general_purpose[rs1] >> 31)
                {
                    shadow->general_purpose[rd] = get_n(s->general_purpose[rs2]) << (32 - s->general_purpose[rs2]);
                }
                shadow->general_purpose[rd] = (shadow->general_purpose[rs1] >> s->general_purpose[rs2]);
            }
            break;
        }
        break;
    case 0b110: //OR
        shadow->general_purpose[rd] = shadow->general_purpose[rs1] & shadow->general_purpose[rs2];
        break;
    case 0b111: //AND
        shadow->general_purpose[rd] = shadow->general_purpose[rs1] & shadow->general_purpose[rs2];
        break;
    }
}

void HandleLUI(CMD cmd)
{
    /*
    handle load upper immediate
    cmd - current instruction
    return: void
    */
    char rd;
    int imm;
    U_Type(cmd, &rd, &imm);
    shadow->general_purpose[rd] = get_n(32);
}

void HandleAUIPC(CMD cmd)
{
    /*
    handle add upper immediate to program counter
    cmd - current instruction
    return: void
    */
    char rd;
    int imm;
    U_Type(cmd, &rd, &imm);
    shadow->general_purpose[rd] = shadow->pc;
}

void HandleJAL(CMD cmd)
{
    /*
    handle jump and link
    cmd - current instruction
    return: void
    */
    char rd = get_rd(cmd);
    shadow->general_purpose[rd] = shadow->pc;
}

void HandleJALR(State* s, CMD cmd)
{
    /*
    handle hump and link register
    s - current state
    cmd - cuurent instruction
    return: void
    */
    char rd = get_rd(cmd);
    char rs1 = (cmd >> 15) & get_n(5);
    shadow->general_purpose[rd]= shadow->pc;
    if (shadow->general_purpose[rs1] != get_n(32))
    {
        shadow->general_purpose[rs1] = get_n(32);
        RecordAccess(s->pc, V);
    }
    shadow->pc = shadow->general_purpose[rs1];
}

void HandleCJUMPS(State* s, CMD cmd)
{
    /*
    handle conditional jumps
    s - state
    cmd - current instruction
    return: void
    */
    char funct3, rs1, rs2;
    short imm;
    B_Type(cmd, &funct3, &rs1, &imm, &rs2);
    if (shadow->general_purpose[rs1] != get_n(32) || shadow->general_purpose[rs2] != get_n(32))
    {
        shadow->general_purpose[rs1] = get_n(32);
        shadow->general_purpose[rs2] = get_n(32);
        RecordAccess(s->pc, V);
    }
}

void HandleStore(State* s, CMD cmd)
{
    /*
    handle storing of values
    s - current state
    cmd - current instruction
    return: void
    */
    char funct3, rs1, rs2;
    short imm;
    S_Type(cmd, &funct3, &rs1, &rs2, &imm);
    int address = s->general_purpose[rs1] + imm;
    unsigned char abits, vbits;
    unsigned char bits8;
    int i;
    unsigned char limit;
    int bits = shadow->general_purpose[rs2];
    switch (funct3)
    {
    case 0b000: //SB
        limit = 1;
    case 0b001: //SH
        limit = 2;
    case 0b010: //SW
        limit = 4;
    }
    for (i = 0; i < limit; i++)
    {
        GetBits(address + i, &abits, &vbits);
        if (!(abits))
        {
            RecordAccess(address, A);
            vbits = get_n(8);
        }
        else
            vbits = bits & get_n(8);
        SetBits(address + i, abits, vbits);
        bits >>= 8;
        GetBits(address + i, &abits, &vbits);
    }
}

void HandleLoad(State* s, CMD cmd)
{
    /*
    handle loading of values
    s - current state
    cmd - current instruction
    return: void
    */
    char funct3, rd, rs1;
    short imm;
    I_Type(cmd, &funct3, &rs1, &rd, &imm);
    int address = s->general_purpose[rs1] + imm;
    char nbits;
    switch (funct3)
    {
    case 0b000: //LB
        nbits = 1 * 8;
    case 0b001: // LH
        nbits = 2 * 8;
    case 0b010: // LW
        nbits = 4 * 8;
    case 0b100: // LBU
        nbits = 1 * 8;
    case 0b101: // LHU
        nbits = 2 * 8;
    }
    shadow->general_purpose[rd] = (get_n(32 - nbits) << nbits) | LoadVN(address, nbits);
}

void HandleALUI(State* s, CMD cmd)
{
    /*
    handle arithmetic and logical operations with constants
    s - state
    cmd - current instruction
    return: void
    */
    char funct3, rs1, rd;
    short imm;
    I_Type(cmd, &funct3, &rs1, &rd, &imm);
    char funct7 = get_funct7(cmd);
    char shamt = imm & get_n(5);
    switch (funct3)
    {
    case 0b000: //ADDI
        shadow->general_purpose[rd] = shadow->general_purpose[rs1];
        break;
    case 0b010: //SLTI
        shadow->general_purpose[rd] = shadow->general_purpose[rs1];
        break;
    case 0b011: //SLTIU
        shadow->general_purpose[rd] = (unsigned)shadow->general_purpose[rs1];
        break;
    case 0b100: //XORI
        shadow->general_purpose[rd] = shadow->general_purpose[rs1] ^ imm;
        break;
    case 0b110: //ORI
        shadow->general_purpose[rd] = shadow->general_purpose[rs1];
        break;
    case 0b111: //ANDI
        shadow->general_purpose[rd] = shadow->general_purpose[rs1];
        break;
    case 0b001: //SLLI
        shadow->general_purpose[rd] = shadow->general_purpose[rs1];
        break;
    case 0b101: //SRLI or SRAI
        switch (funct7)
        {
        case 0b0000000: ;//SRLI
            shadow->general_purpose[rd] = shadow->general_purpose[rs1];
            break;
        case 0b0100000: ;//SRAI
            if (s->general_purpose[rs1] >> 31)
            {
                shadow->general_purpose[rd] = get_n(shamt) << (32 - shamt);
            }
            shadow->general_purpose[rd] = (shadow->general_purpose[rs1] >> shamt);
            break;
        }
    }
}

void addon(State* s)
{
    /*
    execute add on operation
    s - current process state
    return: void
    */
    unsigned int cmd = *(unsigned int*)(s->memory + s->pc);
    unsigned char opcode = cmd & get_n(7);
    switch (opcode) {
        case 0b0110111:
        {
            HandleLUI(cmd);
            break;
        }
        case 0b0010111:
        {
            HandleAUIPC(cmd);
            break;
        }
        case 0b1101111:
        {
            HandleJAL(cmd);
            break;
        }
        case 0b1100111:
        {
            HandleJALR(s, cmd);
            break;
        }
        case 0b1100011:
        {
            HandleCJUMPS(s, cmd);
            break;
        }
        case 0b0000011:
        {
            HandleLoad(s, cmd);
            break;
        }
        case 0b0100011:
        {
            HandleStore(s, cmd);
            break;
        }
        case 0b0010011: //immediate arithmetic and logic operations
        {
            HandleALUI(s, cmd);
            break;
        }
        case 0b0110011: // arithmetic and logical operations
        {
            HandleALU(s, cmd);
            break;
        }
        case 0b1110011: // ecall
        {
            HandleEcall(s);
            break;
        }
    }
}

