#include <stdio.h>

int main()
{
	int i;
	for (i = 0; i < 255; i++)
		printf("%d %02x %3i '%c'\n", i, i, i, i);
	return 0;
}
