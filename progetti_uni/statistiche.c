//stampa la somma dei numeri positivi inseriti (escluso l'ultimo negativo) dopo che si inserisce un numero negativo

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char s[80];
	int n;
	int somma = 0;
	
	fgets(s, sizeof(s), stdin);
	n = atoi(s);
		
	while (n > -1) {
		somma = somma + n;
		
		fgets(s, sizeof(s), stdin);
		n = atoi(s);
	}
	
	printf("[SOMMA]\n%d\n", somma);
	return 0;								
}
