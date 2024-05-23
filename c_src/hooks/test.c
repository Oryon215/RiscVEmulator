#include <stdlib.h>

int main()
{
	char* ptr = malloc(10);
	ptr[0] = 0x41; //'A'
	free(ptr);
	return 1;
}
