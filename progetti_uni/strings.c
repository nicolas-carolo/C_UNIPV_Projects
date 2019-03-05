#include <stdio.h>
#include <string.h>

#define DIM 20

int main()
{
	char nome[DIM];
	char cognome[DIM];
	char s[DIM];

	//inizializzazione del contenuto delle stringhe
	strcpy(s, "");
	strcpy(nome, "Albert");
	strcpy(cognome, "Einstein");

	//composizione della stringa complessiva
	strcat(s, nome);
	strcat(s, " ");
	strcat(s, cognome);

	//stampa della stringa
	puts(s);

	//calcolo e stampa della sua lunghezza
	printf("Lunghezza %d\n", strlen(s));
	
	//identificazione di una sottostringa
	puts(strstr(s, "in"));
	
	//Identificazione di un carattere
	puts(strchr(s, 'e'));
	puts(strrchr(s, 'e'));

	return 0;
}
