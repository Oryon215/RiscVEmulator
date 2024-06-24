#include <stdio.h>

void printX(int a, int b)
{
	printf("%d + %d = %d\n", a, b, a + b);
}

int main()
{
	        int x = 0;
		        int y = 1;
			        printX(x, y);
				        x += y;
					        printX(x,y);
							return 0;
}

