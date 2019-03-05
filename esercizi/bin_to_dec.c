//converte un numero da binario a decimale

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_L 32
#define ZERO 48
#define UNO 49
#define END_VECTOR 10

int main()
{
	char bin[MAX_L] = {0};
	int bin_atoi;
	int i;
	int n;
	int count = 0;
	int dec = 0;

	fgets(bin, sizeof(bin), stdin);	//inserimento numero binario
	
	//controlla che il numero inserito sia positivo
	bin_atoi = atoi(bin);
	if (bin_atoi < 0) {
		puts("ERRORE: Inserire un numero positivo!");
			return 1;
	}

	//conta da quanti numeri è costituito il numero binario inserito
	i = 0;
	while (bin[i] != END_VECTOR) {
		count++;
		i++;
	} 

	//controlla che il numero inserito sia effettivamente un numero binario
	for (i = 0; i < count; i++) {
		if (bin[i] == ZERO || bin[i] == UNO) {}
		else {
			puts("ARGOMENTO NON VALIDO! Inserire un numero in notazione binaria!");
			return 1;
		}
	}

	//itera il processo per il calcolo del numero in base 10 corrispondente
	n = count - 1;
	for (i = 0; i < count; i++) {
		//la costante 48 serve per ottenere i rispettivi valori 0 e 1
		dec = dec + ((bin[i] - 48) * pow(2, n));
		n--;
	}

	//stampa il risultato finale
	printf("[DECIMALE]\n%d\n", dec);

	return 0;
}
