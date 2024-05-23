#include <stdlib.h>

int main()
{
    void* c = malloc(10);
    int* a = (int*)malloc(10);
    char* b = malloc(10);
    int* a2 = malloc(10);
    a = c;
    b = a;
    a2 = (int*)b;
    return 1;
}
