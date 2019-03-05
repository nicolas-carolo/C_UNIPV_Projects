#include <stdio.h>

void swap(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int main ()
{
	int n1 = 10, n2 = 20;
	
	printf("n1 = %i -- n2 = %i\n", n1, n2);
	swap(&n1, &n2);
	printf("n1 = %i -- n2 = %i\n", n1, n2);
	swap(&n1, &n2);
	printf("n1 = %i -- n2 = %i\n", n1, n2);

	return 0;
}
