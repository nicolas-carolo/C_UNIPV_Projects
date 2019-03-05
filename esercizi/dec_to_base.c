#include <stdio.h>
#include <stdlib.h>

int modulo(int num);

int main()
{
	int dec;
	int base;
	//int resto;
	char s[80];
	int convertito[32] = {0};
	int i = 32;
	

	//inserimento del numero da convertire	
	puts("inserisci un numero intero espresso in base 10 da convertire");
	fgets(s, sizeof(s), stdin);
	dec = atoi(s);

	//inserimento della base
	puts("inserisci una base da 2 a 9");
	fgets(s, sizeof(s), stdin);
	base = atoi(s);
	puts("");

	//controlla che la base inserita sia valida
	if (base < 2 || base > 9) {
		puts("base non valida");
		return 1;
	}
	
	//se il numero da convertire è pari a 0 restituisce il valore 0
	if (dec == 0) {
		puts("0");
		return 0;
	}

	if (dec < 0) {
		dec = modulo(dec);
		printf("-");
	}

	while (dec > 0) {
		convertito[i] = dec % base;
		i--;
		dec = dec / base;
	}

	i++; //rimuove lo zero all'inizio della stringa

	while (i < 33) {
		printf("%d", convertito[i]);
		i++;
	}	
	
	printf("\n");

	return 0;
}


int modulo(int num)
{
	return num * (-1);
}
