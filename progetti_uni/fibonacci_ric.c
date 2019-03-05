#include <stdio.h>
#include <stdlib.h>

long fibonacci(long n)
{
	if (n <= 1) return n;
	return fibonacci(n - 1) + fibonacci(n - 2);
}


int main(int argc, char *argv[])
{
	long n;
	
	if (argc != 2) return 1;

	if ((n = atoi(argv[1])) > 0)
		printf("fibonacci (%ld) = %ld\n", n, fibonacci(n));

	return 0;
} 
