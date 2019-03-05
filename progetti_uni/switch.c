#include <stdio.h>
#include <stdlib.h>

int main ()
{
	int n;
	char s[80];

	fgets(s, sizeof(s), stdin);
	n = atoi(s);

	switch (n) {
		case 0:
			puts("il numero immesso vale 0\n");
		case 1:
		case 9:
			puts("n è un quadrato perfetto\n");
			break;
		case 2:
			puts("n è un numero pari pari");
		case 3:
		case 5:
		case 7:
			puts("n è un numero primo\n");
			break;
		case 4:
			puts("n è un quadrato perfetto");
		case 6:
		case 8:
			puts("n è un numero pari\n");
			break;
		default:
			printf("Vengono gestiti solo numeri a singola cifra\n");
		break;
	}
	
	return 0;
}
