#include "cpu.h"
#include <unistd.h>

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
    csr[tvec]

}
