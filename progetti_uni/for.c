//programma che stampa i numeri interi fino all'intero specificato dall'utente

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char s[80];
	int i, n;
	
	fgets(s, sizeof(s), stdin);
	n = atoi(s);
	
	for (i = 0; i <= n; i = i + 1)
		printf("%i\n", i);

	return 0;
}
