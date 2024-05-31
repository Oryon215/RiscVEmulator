#include "../../headers/cpu.h"

/*
Helpful functions
*/

int ChangeBit(unsigned int num, int args, ...)
{
    /*
    turn on/off bit of int at given positions
    args - number of arguments
    num - given number
    ... - unlimited indexes of bits (if negative turn off if positive turn on)
    return number (int)
    */
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
