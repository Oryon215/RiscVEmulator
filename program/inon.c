#include <stdio.h>

int main()
{
	char a[8];

	for (int i = 0; i < 8; i++)
	{
		a[i] = i;
	}
	int* ptr = a;
	printf("%d\n", *ptr);
	return 1;
}
