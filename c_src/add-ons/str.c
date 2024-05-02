#include "../../headers/str.h"
#include <stdio.h>
#include <stdlib.h>

int min(int a, int b)
{
    if (a < b)
        return a;
    return b;
}

int strlen(char* str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        i++;
    }
    return i;
}

unsigned char ConvertC(char c)
{
    if (is_lower(c))
    {
        return c - 'a' + 10;
    }
    if (is_num(c))
    {
        return c - '0';
    }
    if (is_upper(c))
    {
        return c - 'A' + 10;
    }
}

unsigned char ConvertSh(short c)
{
    char c1 = c % 256;
    char c2 = c >> 8;
    return (ConvertC(c1) << 4 )| ConvertC(c2);
}

void Convert(char* c, short* s)
{
    int len = strlen((char *)s) / 2;
    int i;
    for (i = 0; i < len / 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            c[4*(i + 1) - j - 1] = ConvertSh(s[i * 4 + j]);
        }
    }
    if (len % 4 != 0)
    {
        for (int j = 0; j < len % 4; j++)
        {
            c[i * 4 + len % 4 - j - 1] = ConvertSh(s[i * 4 + j]);
        }
    }
}

char* Complete_Hex(int final_len, int num)
{
    char* buffer = (char*)malloc(final_len);
    char* st[8];
    sprintf(st, "%x", num);
    strcpy(buffer, "0x");
    int zero_length = final_len - strlen(st);
    int i;
    for (i = 2; i < zero_length; i++)
    {
        buffer[i] = '0';
    }
    strcpy(buffer + zero_length, st);
    return buffer;
}

int strcpy(char* dst, char* src)
{
    int i, len = strlen(src);
    memcpy1(dst, src, len);
    return len;
}

void memcpy1(unsigned char* dst, unsigned char* src, unsigned int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        dst[i] = src[i];
    }
}

void PrintHexString(unsigned char* buff, unsigned int len)
{
    int i, j;
    printf("memory size: %d\n", len);
    for (i = 0; i < len ; i++)
    {
        char* index = Complete_Hex(10, i);
        char* value = Complete_Hex(2, buff[i]);
        if (i % 4 == 0 && i != 0)
        {
            printf("\n");
        }
        printf("%s: %s ", index, value);
        free(index);
        free(value);
    }

}


