#include <stdio.h>
#include <stdlib.h>

//un anno e' bisestile se e' multiplo di 4 ma non di 100 o se e' multiplo di 400

int main()
{
	char s[80];
	int a;
	
	fgets(s, sizeof(s), stdin);
	a = atoi(s);
	if (((a % 4 == 0) && !(a % 100 == 0)) || (a % 400 == 0))
		printf("Il %d è un anno bisestile\n", a);
	else
		printf("Il %d non è un anno bisestile\n", a);

	return 0;
}
	
