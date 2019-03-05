//programma che esegue l'elevamento a potenza

#include <stdio.h>
#include <stdlib.h>

int main ()
{
	char input1[20];
	char input2[20];
	int base, esponente, potenza, i;

	printf("Scrivi base ed esponente\n");
	fgets (input1, sizeof(input1), stdin);
	fgets (input2, sizeof(input2), stdin);
	base = atoi(input1);
	esponente = atoi(input2);

	potenza = 1;
	
	for(i = 0; i < esponente; i++) {
		potenza = potenza * base;
	}

	printf("Il risultato dell'elevamento a potenza è %i\n", potenza);

	return 0;
}
