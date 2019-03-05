#include <stdio.h>
#include <stdlib.h>

void num_print(int n, int i)
{
	if (i > n) return;
	printf ("%d\n", i);
	i++;
	num_print(n, i);
}


int main(int argc, const char *argv[])
{
	int n;
	n = atoi(argv[1]);
	num_print(n, 1);

	return 0;
}
