//programma che stampa a video un triangolo rettangolo di '*' il cui numero di * per cateto viene inserito dall'utente

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char s[80];
	int i, j, cateto;

	//inserimento dimensioni base
	printf("inserire il numero di asterischi per cateto\n");
	fgets(s, sizeof(s), stdin);
	cateto = atoi(s);

	for (i = 0 ; i < cateto; i++){
        	for (j = 0; j < i; j++)
        	printf ("*");
        	printf ("*\n");
    	}


	return 0;
}
