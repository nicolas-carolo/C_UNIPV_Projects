#include <stdio.h>
#include <stdlib.h>

//programma che stampa il valore di nut se e solo se il numero e' primo

int main()
{
	char s[80];
	int i, max, nut;	//nut = number under test

	fgets(s, sizeof(s), stdin);
	max = atoi(s);

	for (nut = 2; nut < max; nut++); {
		for (i = 2; i < nut; i++) {
			if (nut % i ==0)
				break;
		}
		if (i ==nut)
			printf("%i\n", nut);
	}
	return 0;
}
