#include <stdio.h>
#include <stdlib.h>

int main()
{
	char s[80];
	int n;

	do  {
		fgets(s, sizeof(s), stdin);
		n = atoi(s);
		
		if (n < 0) {
			printf(" %d < 0: uscita dal loop...\n", n);
			break;
		}

		if (n > 10) {
			printf(" %d > 10 non ammesso\n", n);
			continue;
		}
		printf("%d è il valore immesso\n", n);
	} while(1);

	return 0;
} 
