#include <stdio.h>

int pow1(int a, int b)
{
	if (b == 0)
		return 1;
	return a * pow1(a, b - 1);
}

int main()
{
	int a = 2, b = 2;
	printf("%d\n", pow1(a, b));
	a++;
	printf("%d\n", pow1(a, b));
	return 0;
}
