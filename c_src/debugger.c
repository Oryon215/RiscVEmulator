#include "../headers/cpu.h"

void Break(State* s, int b)
{
    s->breakpoints[s->current_breakpoint % MaxBreakpoints] = b;
    s->current_breakpoint ++;
}

void BreakString(State* s, char* st)
{
    int i = 1;
    char* st2 = st;
    while (st2[i - 1] != ' ' && st2[i - 1] != 0x0)
    {
        i++;
    }

    st2+=i;
    st2+=2;
    int b = ExtractFirstNumber(st2, 16);
    Break(s, b);
    printf("Breakpoint set at 0x%x.\n", b);
}

int ExtractFirstNumber(const char *str, int base) {
    char *endptr;
    long num = strtol(str, &endptr, base);

    return (int)num;
}

void CheckBreapoints(State* s)
{
    for (int i = 0; i < s->current_breakpoint; i++)
    {
        if (s->pc == s->breakpoints[i])
        {
            BreakPoint(s);
            return;
        }
    }
}

void BreakPoint(State* s)
{
    while (1)
    {
        printf("Breakpoint at 0x%x\n", s->pc);
        printf("->");
        char* buffer = (char*)malloc(20);
        fgets(buffer, 20, stdin);
        switch ((unsigned int)buffer[0])
        {
        case (unsigned int)'q':
            exit(0);
            break;
        case (unsigned int)'p':
            PrintMemory(s, buffer);
            break;
        case (unsigned int)'c':
            return;
        case (unsigned int)'b':
            BreakString(s, buffer);
            break;
        case 23:
            continue;
        default:
            printf("Operation not permitted.\n");
            break;
        }
        free(buffer);
    }
}

void PrintMemory(State* s, char* st)
{
    int i = 1;
    char* st2 = st;
    while (st2[i - 1] != ' ' && st2[i - 1] != 0x0)
    {
        i++;
    }
    st2+=i;
    if (st2[0] == 'x')
    {
        st2+=1;
        int num = ExtractFirstNumber(st2, 10);
        if (in_range(0, num, 32))
        {
            printf("x%d=%d\n", num, s->general_purpose[num]);
        }
        else
        {
            printf("Symbol %s unrecognized.\n", st2);
        }
    }
    if (st2[0] == '*')
    {
        st2+=3;
        int num = ExtractFirstNumber(st2, 16);
        if (CheckOperation(s, R, num, 0))
        {
            printf("0x%x:%d\n", num, s->memory[num]);
        }
        else
        {
            printf("Operation not permitted\n");
        }
    }
    if (st2[0] == 'p' && st2[1] == 'c')
    {
        printf("pc=%d\n", s->pc);
    }

}
