#ifndef STR_H_INCLUDED
#define STR_H_INCLUDED
#include <stdlib.h>
#define is_lower(c) (c >= 'a' && c <= 'z')
#define is_upper(c) (c >= 'A' && c <= 'Z')
#define is_num(c) (c >= '0' && c <= '9')
int strlen(char* str);
unsigned char ConvertC(char c);
unsigned char ConvertSh(short c);
void Convert(char* c, short* s);
int strcpy(char* dst, char* src);
void PrintHexString(unsigned char* buff, unsigned int len);
void memcpy1(unsigned char* dst, unsigned char* src, unsigned int n);
char strcmp1(char* st1, char* st2);
#endif // STR_H_INCLUDED
