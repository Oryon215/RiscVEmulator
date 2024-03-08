#ifndef STR_H_INCLUDED
#define STR_H_INCLUDED
#include <stdlib.h>
#define is_lower(c) (c >= 'a' && c <= 'z')
#define is_upper(c) (c >= 'A' && c <= 'Z')
#define is_num(c) (c >= '0' && c <= '9')
int strlen(char* str);
unsigned char ConvertC(char c);
unsigned char ConvertSh(short c);
unsigned char* Convert(short* c);
int strcpy(char* dst, char* src);

#endif // STR_H_INCLUDED
