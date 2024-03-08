#include "cpu.h"
#include "str.h"
#include <stdio.h>
State* init_state()
{
    State* s = (State*)malloc(sizeof(State));
    for (int i = 0; i < 32; i++)
    {
        s->general_purpose[i] = 0;
    }
    int size;
    printf("Enter memory size:\n");
    scanf("%d", &size);
    s->memory_size = size;
    size *= 2;
    char* buffer = malloc(size);
    printf("Enter program memory:\n");
    scanf("%s", buffer);
    buffer[size] = '\0';
    s->memory = (char *)Convert((short*)buffer);
    s->pc = 0;
    return s;
}

void init_csr(State* s)
{
    int* csr = s->csr;
    csr[mvendorid] = 0x496e6f6e; // manufacturer - Inon
    csr[marchid] = 0; // microarchitecture - unknown
    csr[mimpid] = 0; //machine implementation id - unknown
    csr[mhartid] = getpid(); // current thread id

    csr[mstatus] = 0;
    csr[medeleg] = 0;
    csr[mideleg] = 0;
    csr[mie] = 0;
    csr[tvec] = &

}

int main() {
    State* s = init_state();
    EmulateRiscV(s);
}
