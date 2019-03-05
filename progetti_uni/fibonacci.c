//mostra la serie di Fibonacci fino al numero inserito

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char s[80];
	int f1 = 1, f2 = 1;
	int f3, i, n;

	fgets(s, sizeof(s), stdin);
	n = atoi(s);
	if (n >= 1) printf("%i\n", f1);
	if (n >= 2) printf("%i\n", f2);
	for (i = 3; i <= n; i++) {
		f3 = f1 + f2;
		printf("%i\n", f3);
		f1 = f2;
		f2 = f3;
	}
	return 0;
}	
