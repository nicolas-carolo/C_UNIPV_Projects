#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char pilota[40];
	//char team[40];
	int punteggio;
} Dati;

int main()
{
	char buf[300];
	int i;
	int punteggio[20] = {25, 18, 15, 12, 10, 8, 6, 4, 2, 1};
	char pilota[40];
	//char team[40];
	Dati vect[20];
	FILE *fin;
	
	if (!(fin = fopen("campionato1.txt", "r"))) {
		puts("ERRORE: il file di input \"campionato.txt\" non è stato trovato");
		return 1;
	}
	
	for (i = 0; i < 20; i++) {
		fgets(buf, sizeof(buf), fin);
		sscanf(buf, "%s", pilota);

		strcpy(vect[i].pilota, pilota);
		vect[i].punteggio = punteggio[i];
		//strcpy(vect[i].team, team);
	}

	puts("[ORDINE_PILOTI]");
	for (i = 0; i < 20; i++) {
		printf("%s %d\n", vect[i].pilota, vect[i].punteggio);
	}
	
	fclose(fin);
	return 0;
}
