//programma che effettua la lettura di una serie di numeri reali. Il programma termina quando viene immesso un numero pari a zero. Calcolare e stampare la media aritmetica dei valori inseriri

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char s[80];
	double n;
	double somma = 0;
	double media = 0;
	int i = 0;

	fgets(s, sizeof(s), stdin);
	n = atoi(s);
	somma = n;
	i++;
	
	while (n != 0) {
		fgets(s, sizeof(s), stdin);
		n = atoi(s);
		somma = somma + n;
		i++;
	}
		media = (double)somma / (i - 1);
		printf("La media dei numeri inseriti è %lf\n", media);
		return 0;
}
