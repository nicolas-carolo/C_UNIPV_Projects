//ESERCIZIO 5 CAPITOLO 8

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char squadra[11];
	int vinte;
	int perse;
	int pareggiate;
	int gf;
	int gs;
} Input;

typedef struct {
	char squadra[11];
	int giocate;
	int punteggio;
	double media_gf;
	double media_gs;
} Output;

int partite_giocate(int vinte, int perse, int pareggiate);
int calcola_punteggio(int vinte, int pareggiate);
double calcola_media_gf(int gf, int giocate);
double calcola_media_gs(int gs, int giocate);

int main()
{
	char squadra[11];
	int vinte;
	int perse;
	int pareggiate;
	int gf;
	int gs;
	Input vect[18];
	Output dati[18];
	int i;
	int nread;
	char s[100];
	FILE *fin;

	if(!(fin = fopen("girone_input", "r"))) {
		puts("ERRORE: il file di input \"girone_input\" non è stato trovato!");
		return 1;
	}
	
	for (i = 0; i < 18; i++) {
		fgets(s, sizeof(s), fin);

		nread = sscanf(s, "%s %i %i %i %i %i", squadra, &vinte, &perse, &pareggiate, &gf, &gs);

		if (nread != 6) {
			puts("ERRORE: file corrotto!");
			return 1;
		}

		if (strlen(squadra) > 10) {
			puts("ERRORE: Il nome della squadra non può contenere più di 10 caratteri!");
			return 1;
		}

		strcpy(vect[i].squadra, squadra);
		vect[i].vinte = vinte;
		vect[i].perse = perse;
		vect[i].pareggiate = pareggiate;
		vect[i].gf = gf;
		vect[i].gs = gs;	
	}

	fclose(fin);

	//for (i = 0; i < 18; i++) {
	//	printf("squadra: %s\nvinte: %i\nperse: %i\npareggiate: %i\ngoal fatti: %i\ngoal subiti: %i\n\n", vect[i].squadra, vect[i].vinte, vect[i].perse, vect[i].pareggiate, vect[i].gf, vect[i].gs);
	//}

	//puts("\n[PARTITE GIOCATE]");
	for (i = 0; i < 18; i++) {
		dati[i].giocate = partite_giocate(vect[i].vinte, vect[i].perse, vect[i].pareggiate);
		//printf("%s: %d\n", vect[i].squadra, dati[i].giocate);
	}

	//puts("\n[PUNTEGGIO]");
	for (i = 0; i < 18; i++) {
		dati[i].punteggio = calcola_punteggio(vect[i].vinte, vect[i].pareggiate);
		//printf("%s: %d\n", vect[i].squadra, dati[i].punteggio);
	}

	//puts("\n[MEDIA GF PER PARTITA]");
	for (i = 0; i < 18; i++) {
		dati[i].media_gf = calcola_media_gf(vect[i].gf, dati[i].giocate);
		//printf("%s: %lf\n", vect[i].squadra, dati[i].media_gf);
	}

	//puts("\n[MEDIA GS PER PARTITA]");
	for (i = 0; i < 18; i++) {
		dati[i].media_gs = calcola_media_gs(vect[i].gs, dati[i].giocate);
		//printf("%s: %lf\n", vect[i].squadra, dati[i].media_gs);
	}

	fin = fopen("girone_output", "w");

	fprintf(fin, "squadra, giocate, punteggio, goal fatti/partita, goal subiti/partita\n");
	for (i = 0; i < 18; i++) { 
		fprintf(fin, "%s %i %i %.3lf %.3lf\n", vect[i].squadra, dati[i].giocate, dati[i].punteggio, dati[i].media_gf, dati[i].media_gs);
	}

	fclose(fin);

	puts("Il file di output \"girone_output\" è stato generato con successo!");
	return 0;
}


int partite_giocate(int vinte, int perse, int pareggiate)
{
	return vinte + perse + pareggiate;
}


int calcola_punteggio(int vinte, int pareggiate)
{
	return 3 * vinte + pareggiate;
}


double calcola_media_gf(int gf, int giocate)
{
	return (double)gf / giocate;
}


double calcola_media_gs(int gs, int giocate)
{
	return (double)gs / giocate;
}
