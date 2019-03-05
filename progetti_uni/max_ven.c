//programma che effettua la lettura di una serie di numeri interi. Il programma termina quando viene immesso un numero pari a zero. Poi stampa il maggiore

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char s[80];
	int n;
	int max;
	
	fgets(s, sizeof(s), stdin);
	n = atoi(s);
	max = n;

	while (n != 0) {
		if (n > max) {
			max = n;
		}
		
		fgets(s, sizeof(s), stdin);
		n = atoi(s);
	}
	
	printf("Il numero massimo è %d\n", max);
	return 0;		
}
