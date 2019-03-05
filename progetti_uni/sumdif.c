//programma che effetttua la somma tra due interi

#include <stdio.h>

int main()
{
	int a, b, somma, diff;
	a = 10;
	b = 12;
	somma = a + b;
	diff = a - b;
	printf("La somma è %i, mentre la differenza è %i\n", somma, diff);
	/* il programma funzionerebbe anche sostituendo la riga soprastante con la seguente riga
	printf("La somma è %i, mentre la differenza è %i\n", a + b, a - b); */
	return 0;
}
