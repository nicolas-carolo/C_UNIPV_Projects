//calcolo di un istogramma

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N ('Z' - 'A' + 1) //direttiva del preprocessore

int chist(const char testo[], int *h);

int main()
{
	int h[N] = {0};
	char testo[80];
	int i;

	while (fgets(testo, sizeof(testo), stdin)) {	//il programma si ferma premendo CTRL+D
		chist(testo, h);
	}
	
	for (i = 0; i < N; i++) {
		printf("Cont(%c) = %d\n", 'A' + i, h[i]);
	}
	
	return 0;
}


int chist(const char testo[], int *h)
{
	int len;
	int i;

	len = strlen(testo);
	
	for (i = 0; i < len; i++) {	//qui manca un pezzo ATTENZIONE!!!
		if ((testo[i] >= 'A' && testo[i] <= 'Z') || (testo[i] >= 'a' && testo[i] <= 'z')) {
		if (isalpha(testo[i]))
			h[toupper(testo[i]) - 'A']++;	//toupper converte in maiuscolo una lettera minuscola
		}

	}
	
	return len;
}
