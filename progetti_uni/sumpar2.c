//programma per la somma di due decimali

#include <stdio.h>
#include <stdlib.h>

int main()
{
	double a, b;
	char s[80];

	fgets(s, sizeof(s), stdin);
	a = atof(s);
	fgets(s, sizeof(s), stdin);
	b = atof(s);
	printf("%lf + %lf = %lf\n", a, b, a + b);

	return 0;
}
