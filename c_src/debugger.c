#include "../headers/cpu.h"

#define symbol_table_entry_size 16
#define text_section_index 1
#define section_header_index 14
#define section_header_size_index 20
#define symbol_addr_index 4

void Break(State* s, int b)
{
    s->breakpoints[s->current_breakpoint % MaxBreakpoints] = b;
    s->current_breakpoint ++;
    printf("Breakpoint set at 0x%x.\n", b);
}

void BreakString(State* s, char* st)
{
    int i = 1;
    char* st2 = st;
    st2[strlen(st2) - 1] = 0x0;
    if (strcmp1(st2, "b n"))
    {
        Break(s, s->pc + 4);
        return;
    }
    while (st2[i - 1] != ' ' && st2[i - 1] != 0x0)
    {
        i++;
    }

    st2+=i;
    st2+=2;
    int b = ExtractFirstNumber(st2, 16);
    Break(s, b);
}

void PrintSymbol(State* s)
{
    for (int i = 0; i < s->symtab_size / symbol_table_entry_size; i++)
    {
        short* ptr_shndx = s->symtab + i * symbol_table_entry_size + section_header_index;
        if (*ptr_shndx == text_section_index)
        {
            int* ptr_addr = s->symtab + i * symbol_table_entry_size + symbol_addr_index;
            if (s->pc == *ptr_addr)
            {
                int* ptr_name = s->symtab + i * symbol_table_entry_size;
                printf("%d: %s\n", s->pc, s->strtab + *ptr_name);
            }
        }
    }
}

void PrintMemory(State* s, char* st)
{
    int i = 1;
    char* st2 = st;
    if (strcmp1(st, "p state"))
    {
        PrintState(s);
    }
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

void BreakPoint(State* s)
{
    printf("%s\n", instruction);
    PrintSymbol(s);
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
        case '\n':
            continue;
        default:
            printf("Operation not permitted.\n");
            break;
        }
        free(buffer);
    }
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
