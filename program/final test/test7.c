#include <stdio.h>

int main()
{
	int x = 0;
	int* ptr = &x;
	printf("%p\n", ptr);
	printf("%d\n", *ptr);
	*ptr = 1;
	printf("%d\n", x);
}
