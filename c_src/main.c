#include "../headers/cpu.h"
State* MakeState1()
{
    /*
    return: new state struct ptr ready for use 
    */
    State* s = (State*)malloc(sizeof(State));
    s->csr[misa] = 0;
    s->csr[misa] = ChangeBit(s->csr[misa], 5, 7, 9, 13, 19, 32); // 32 bit, I, M, Zicsr and S Mode extensions
    s->csr[mvendorid] = (int)"inon";
    s->csr[marchid] = 0; //not implemented
    s->csr[mimpid] = 0; //not implemented
    s->csr[mhartid] = getpid();
    s->csr[mstatus] = 0;
    s->csr[mstatus] = ChangeBit(s->csr[mstatus], 2, 2, 4);
    s->csr[medeleg] = (1 << 8);
    s->csr[mideleg] = 0;
    s->csr[mtvec] = (int)MIVT;
    s->csr[stvec] = (int)SIVT;
    for (int i = 0; i < 32; i++)
    {
        s->general_purpose[i] = 0;
    }
    s->pc = 0;
    s->current_breakpoint = 0;

}

void MakeStateMemory1(State* s) {
    /*
    Manually manage state memory
    s - state ptr (State*)
    return: void
    */
    printf("Enter memory size:\n");
    scanf("%d", &s->memory_size);
    s->memory = (unsigned char*)malloc(s->memory_size * sizeof(unsigned char));

    printf("Enter program memory:\n");
    char* string = malloc(s->memory_size);
    scanf("%s", string);
    Convert(s->memory, (short*)string);
    free(string);
}

int main(int argc, char** argv)
{
    /*
    Manage process run
    argc - argument count (int)
    argv - argument vector (char**)
    return: 1 on success 
    */
    char* filename = "./program/a.out";
    char* dllname = "./c_src/tools/null.so";
    if (argc > 1)
    {
        filename = argv[1];
    }
    if (argc > 2)
    {
        dllname = argv[2];
    }
    State* s = MakeState1();
    void* ptr = Load(s, filename, dllname);
    Break(s, s->pc);
    EmulateRiscV(s);
    free(s);
    dlclose(ptr);
    return 1;
}
