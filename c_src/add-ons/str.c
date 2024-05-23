#include "../../headers/str.h"
#include <stdio.h>
#include <stdlib.h>

int min(int a, int b)
{
    if (a < b)
        return a;
    return b;
}

int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

unsigned int strlen1(char* str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        i++;
    }
    return i;
}

char strcmp1(char* st1, char* st2)
{
    int i = 0;

    if (strlen1(st1) != strlen1(st2))
        return 0;
    while (i < strlen1(st1) && st1[i] == st2[i])
    {
        i++;
    }
    return i == strlen1(st1);
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
    int len = strlen1((char *)s) / 2;
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
    char st[8];
    sprintf(st, "%x", num);
    strcpy1(buffer, "0x");
    int zero_length = final_len - strlen1(st);
    int i;
    for (i = 2; i < zero_length; i++)
    {
        buffer[i] = '0';
    }
    strcpy1(buffer + zero_length, st);
    return buffer;
}

unsigned int strcpy1(char* dst, char* src)
{
    int i, len = strlen1(src);
    memcpy1(dst, src, len);
    dst[len] = 0x0;
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
    int i;
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

void Print2(unsigned char* buff, unsigned int len, char* format)
{
    int i;
    for (i = 0; i < len; i++)
    {
        printf("%d: ", i);
        printf(format, buff[i]);
        if (i % 4 == 0 && i != 0)
        {
            printf("\n");
        }
    }

}

void Print1(unsigned char* buff, unsigned int len, char* format)
{
    int i;
    for (i = 0; i < len; i++)
    {
        printf(format, buff[i]);
        if (buff[i] == 0x0)
        {
            printf(" ");
        }
    }

}


