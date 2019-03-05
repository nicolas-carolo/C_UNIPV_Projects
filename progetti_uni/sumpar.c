#include <stdio.h>
#include <stdlib.h> // libreria per usare la funzione atoi

int main()
{
	char s[80]; //s è un vettore di 80 caratteri ASCII
	int a, b;

	fgets(s, sizeof(s), stdin);		//sizeof indica la massima lunghezza accettata da tastiera
	a = atoi(s);				//converte s in un intero che viene assegnato alla variabile a
	fgets(s, sizeof(s), stdin);		//stdin = standard input. fgets ci permette di leggere anche da un file e non solo da tastiera
	b = atoi(s);
	printf("%i + %i = %i\n", a, b, a + b);
	return 0;
}
