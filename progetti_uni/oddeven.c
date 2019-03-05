//controlla se un numero è pari o dispari

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char s[80];
	int i, j;

	fgets(s, sizeof(s), stdin);
	i = atoi(s);
	j = i / 2;
	
	if (j * 2 == i) {
		printf("%i: pari\n", i);
		return 0;
	}
	printf("%i: dispari\n", i);
	return 0;
}
