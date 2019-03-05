//genera la sequenza di Collatz
//dato un numero
//se e' pari il numero successivo e' dato dalla sua meta'
//se e' dispari il numero successivo e' dato dal suo triplo piu' uno

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char s[80];
	int i, j = 0;
	
	fgets(s, sizeof(s), stdin);
	i = atoi(s);
	
	while (i != 1) {
		printf("[%2i] %i\n", j, i);
		
		if (i % 2)
			i = 3 * i + 1;
		else
			i = i / 2;
		
		j = j + 1;
	}

	return 0;
}
