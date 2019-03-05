//esercizio 6 del capitolo 4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_L 32
#define ZERO 48
#define UNO 49
#define OTTO 56
#define NOVE 57
#define DIECI 65
#define QUINDICI 70
#define A_MINUSC 97
#define F_MINUSC 102
#define MENO 45
#define END_VECTOR 10

int main()
{
	char numero[MAX_L] = {0};
	char b[3];
	//int a;
	int base;
	int i;
	int count = 0;

	//inserimento stringa da valutare
	puts("Inserisci una stringa da valutare");
	fgets(numero, sizeof(numero), stdin);

	//inserimento base
	puts("Inserisci una base");
	fgets(b, sizeof(b), stdin);
	base = atoi(b);

	//se la stringa rappresenta un numero negativo la converte in positivo
	if (numero[0] == MENO) {
		for (i = 0; i < MAX_L; i++) {
			numero[i] = numero [i + 1];
		}
	}
	
	//conta da quanti caratteri è costituito il numero inserito
	i = 0;
	while (numero[i] != END_VECTOR) {
		count++;
		i++;
	} 

	//converte le lettere a,b,c,d,e,f inserite in maiuscole 
	for (i = 0; i < count; i++) {
		if (numero[i] >= A_MINUSC && numero[i] <= F_MINUSC) {
			numero[i] = toupper(numero[i]);
		}	
	}
	

	switch (base) {
		case 2:	//base 2
			for (i = 0; i < count; i++) {
				if (numero[i] == ZERO || numero[i] == UNO) {}
				else {
					puts("Stringa NON valida come numero espresso in base 2");
					return 0;
				}
			}
			puts("Stringa valida come numero espresso in base 2");
			return 0;

		case 8:	//base 8
			for (i = 0; i < count; i++) {
				if (numero[i] >= ZERO && numero[i] < OTTO) {}
				else {
					puts("Stringa NON valida come numero espresso in base 8");
					return 0;
				}
			}
			puts("Stringa valida come numero espresso in base 8");
			return 0;

		case 10: //base 10
			for (i = 0; i < count; i++) {
				if (numero[i] >= ZERO && numero[i] <= NOVE) {}
				else {
					puts("Stringa NON valida come numero espresso in base 10");
					return 0;
				}
			}
			puts("Stringa valida come numero espresso in base 10");
			return 0;

		case 16: //base 16
			for (i = 0; i < count; i++) {
				if ((numero[i] >= ZERO && numero[i] <= NOVE) || (numero[i] >= DIECI && numero[i] <= QUINDICI)) {}
				else {
					puts("Stringa NON valida come numero espresso in base 16");
					return 0;
				}
			}
			puts("Stringa valida come numero espresso in base 16");
			return 0;
		
		default: //restituisce un errore se la base inserita non è valida
			puts("ERRORE: base non valida! Basi valide: 2, 8, 10, 16");
			return 0;
		
	}
	
}
