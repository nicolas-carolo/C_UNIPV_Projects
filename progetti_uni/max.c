//Permette l'inserimento dei numeri da parte dell'utente finche' non immette il valore zero. A questo punto dice qual e' il numero massimo

#include <stdio.h>
#include <stdlib.h>

int main ()
{
	char s[80];
	int a,max;
	
	fgets(s, sizeof(s), stdin);
	a = atoi(s);
	max = a;

	while (a != 0) {
		if (max < a) 
			max = a;
		fgets(s, sizeof(s), stdin);
		a = atoi(s);
	}
	
	printf("il numero massimo è %i\n", max);
	return 0;	

}
