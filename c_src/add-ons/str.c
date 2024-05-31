#include "../../headers/str.h"
#include <stdio.h>
#include <stdlib.h>

int min(int a, int b)
{
    /*
    get min number out of two
    a - number
    b - number
    return minimum of a and b
    */
    if (a < b)
        return a;
    return b;
}

int max(int a, int b)
{
        /*
    get max number out of two
    a - number
    b - number
    return maximum of a and b
    */
    if (a > b)
        return a;
    return b;
}

unsigned int strlen1(char* str)
{
    /*
    get length of given string
    str - string ptr
    return string length
    */
    int i = 0;
    while (str[i] != '\0')
    {
        i++;
    }
    return i;
}

char strcmp1(char* st1, char* st2)
{
    /*
    compare between strings
    st1 - string ptr
    st2 - string ptr
    return 0 if not equal and 1 otherwise
    */
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
    /*
    convert char to hex value
    c - char
    return hex value of char (if has one)
    */
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
    /*
    convert short to hex number
    c - short composed of 2 chars
    return symbolic hex value of short
    */
    char c1 = c % 256;
    char c2 = c >> 8;
    return (ConvertC(c1) << 4 )| ConvertC(c2);
}

void Convert(char* c, short* s)
{
    /*
    convert short s composed of hex symbolic values to char c composed of hexadecimal values
    c - char ptr
    s - short ptr
    return: void
    */
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
    /*
    complete hexadecimal value to length
    final_len - length of hexadecimal value
    num - initial value
    return: string of hex value in length final_len
    */
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
    /*
    copy string from src to dst
    dst - str ptr
    src - str ptr
    return number of chars copied
    */
    int i, len = strlen1(src);
    memcpy1(dst, src, len);
    dst[len] = 0x0;
    return len;
}

void memcpy1(unsigned char* dst, unsigned char* src, unsigned int n)
{
    /*
    copy memory from one buffer to another
    dst - ptr buffer
    src - ptr buffer
    n - num of chars copied
    return: void
    */
    int i;
    for (i = 0; i < n; i++)
    {
        dst[i] = src[i];
    }
}

void PrintHexString(unsigned char* buff, unsigned int len)
{
    /*
    print string representing hex values
    buff - string
    len - length of string
    return: void
    */
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
    /*
    print string with addresses in decimal format
    buff - ptr buffer
    len - length of buffer
    format - format of string
    return: void
    */
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
    /*
    print string without addresses
    buff - ptr buffer
    len - length of buffer
    format - format of string
    return: void
    */
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


