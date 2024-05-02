#include "../../headers/cpu.h"
int ChangeBit(unsigned int num, int args, ...)
{
    int i, index;
    va_list lst;
    va_start(lst, args);

    for (i = 0; i < args; i++)
    {
        index = va_arg(lst, int);
        if (index < 0)
        {
            index *= -1;
            num &= (int)pow(2, 32) ^ (1 << index);
        }
        else
        {
            num |= (1 << index);
        }
    }
    return num;


}
