//permette l'inserimento di numeri finche' non si immette zero. Poi dice se ci sono dei numeri consecutivi uguali

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char s[80];
	int n;
	int prev;
	int i = 0;

	fgets(s, sizeof(s), stdin);
	n = atoi(s);
	
	while (n != 0) {
		prev = n;
		
		fgets(s, sizeof(s), stdin);
		n = atoi(s);

		if (n == prev) {
			i++;
		}

	}
	
	if (i != 0) {
		printf("Ci sono dei numeri uguali consecutivi\n");
		return 0;
	}
	else {
		printf("Non ci sono dei numeri uguali consecutivi\n");
		return 0;
	}
}
			
