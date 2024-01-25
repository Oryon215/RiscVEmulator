#include "cpu.h"

int main() {
    State *s = (State*)malloc(sizeof(State));
    s->pc = 0;
    s->memory = (unsigned char*)malloc(4);
    s->memory[0] = 0xb7;
    s->memory[1] = 0x20;
    s->memory[2] = 0x00;
    s->memory[3] = 0x00;

    EmulateRiscV(s); //test LUI

    free(s->memory);
    free(s);
    return 0;
}
