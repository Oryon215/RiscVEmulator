#include "str.h"
#include <stdio.h>

int strlen(char* str)
{
    int len = 0;
    while(str[len] != '\0')
    {
        len ++;
    }
    return len;
}

int strcpy(char* dst, char* src)
{
    int i, length = strlen(src);

    for (i = 0; i < length; i++)
    {
        *(dst + i) = *(src + i);
    }
    return i;
}

unsigned char ConvertC(char c)
{
    unsigned char val;
    if (is_upper(c))
    {
        val = c - 'A' + 10;
    }
    if (is_lower(c))
    {
        val = c - 'a' + 10;
    }
    if (is_num(c))
    {
        val = c - '0' ;
    }
    return val;
}

unsigned char ConvertSh(short c)
{
    unsigned char low_order = c >> 8;
    unsigned char high_order = c & 0x00ff;
    unsigned char val = ConvertC(high_order) * 16 + ConvertC(low_order);
    return val;
}

unsigned char* Convert(short* c)
{
    int length = strlen((char *)c) / 2;
    unsigned char* arr = malloc(length + 1);
    for (int i = 0; i < length; i ++)
    {
        int index = 4* (i /4 + 1) - 1 - i % 4;
        arr[i] = ConvertSh(c[index]);
    }
    arr[length] = '\0';
    return arr;
}

void PrintHexString(unsigned char* buff, unsigned int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        if (i !=0 && !(i % 10))
        {
            printf("\n");
        }
        printf("%d: %x ", i, buff[i] );
    }
    printf("%d: %x\n", i, buff[i]);
}


