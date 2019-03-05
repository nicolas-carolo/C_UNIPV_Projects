//programma che esegue l'elevamento a potenza dati due numeri a e b attraverso l'implementazione di un ciclo for

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int a;
	int b;
	int i;
	int potenza = 1;
	char s[80];

	printf("Inserisci la base della potenza\n");
	fgets(s, sizeof(s), stdin);
	a = atoi(s);
	printf("Inserisci l'esponente della potenza\n");
	fgets(s, sizeof(s), stdin);
	b = atoi(s);

	for (i = 0; i < b; i++) {
		potenza = potenza * a;
	}

	if ((a != 0) && (b != 0)) {
		printf("%d ^ %d = %d\n", a, b, potenza);
		return 0;
	}
	else {
		printf("Operazione senza senso!\n");
		return 0;
	}

	
}
