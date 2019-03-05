#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int id;
	int width;
	int height;
	char p_inside[50];	//persona nell'immagine
	char p_riconosciuta[50]; //persona riconosciuta dal sistema
} Immagine;

typedef struct {
	char nome[50];
	int frequenza;
	double perc_frequenza;
	int ric_corretti;
	double perc_ric_corretti;
} Persona;

int f_numero_riconoscimenti_errati(Immagine *vect, int n);
void f_numero_riconoscimenti_corretti(Immagine *vect, int n, int n_errori);
void f_statistiche(Immagine *vect, int n, int n_errori);
void swap(Immagine *a, Immagine *b);
int f_calc_area(int w, int h);
void f_ordina_aree(Immagine *vect, int n);

int main (int argc, char *argv[])
{
	FILE *fin;
	char buf[512];
	int n;
	int i = 0;
	int n_errori;
	Immagine *vect;


	if (argc != 2) {
		printf("USO: %s input_file\n", argv[0]);
		return 1;
	}

	if (!(fin = fopen(argv[1], "r"))) {
		printf("ERRORE: impossibile aprire il file di input \"%s\"\n", argv[1]);
		return -1;
	}

	fgets(buf, sizeof(buf), fin);
	n = atoi(buf);

	vect = malloc(n * sizeof(Immagine));

	for (i = 0; i < n; i++) {
		fgets(buf, sizeof(buf), fin);
		sscanf(buf, "%d %d %d %s %s", &vect[i].id, &vect[i].width, &vect[i].height, vect[i].p_inside, vect[i].p_riconosciuta);
	}

	n_errori = f_numero_riconoscimenti_errati(vect, n);
	f_numero_riconoscimenti_corretti(vect, n, n_errori);
	f_statistiche(vect, n, n_errori);
	f_ordina_aree(vect, n);
	
	fclose(fin);
	free(vect);

	return 0;
}


int f_numero_riconoscimenti_errati(Immagine *vect, int n)
{
	//funzione che stampa a video il numero dei riconoscimenti errati e la relativa percentuale sul totale
	int i;
	int n_errori = 0;
	double perc_errori;

	for (i = 0; i < n; i++) {
		if (strcmp(vect[i].p_riconosciuta, "ERRORE") == 0) {
			n_errori++;	
		}
	}

	perc_errori = (double)n_errori * 100 / n;

	printf("%d riconoscimenti errati su %d (%lf)\n", n_errori, n, perc_errori);

	return n_errori;
}


void f_numero_riconoscimenti_corretti(Immagine *vect, int n, int n_errori)
{
	//funzione che stampa a video il numero dei riconoscimenti avvenuti correttamente e la relativa percentuale sul totale
	int i;
	int n_corretti = 0;
	double perc_corretti;

	for (i = 0; i < n; i++) {
		if (strcmp(vect[i].p_inside, vect[i].p_riconosciuta) == 0) {
			n_corretti++;
		}
	}

	perc_corretti = (double)n_corretti * 100 / (n - n_errori);

	printf("%d riconoscimenti corretti su %d (%lf)\n", n_corretti, n - n_errori, perc_corretti);
}


void f_statistiche(Immagine *vect, int n, int n_errori)
{
	//funzione che stampa a video il numero di volte in cui ogni persona compare in una foto e la relativa percentuale sul totale delle foto
	//senza contare le foto con riconoscimenti errati. Inoltre stampa, per ogni persona, il numero delle volte in cui il suo volto viene
	//riconosciuto correttamente e la relativa percentuale
	int i;
	int j;
	int n_persone = 0;
	char pers_analisi[50];
	int count_pers = 0;
	int d = 10;
	Persona *vect_pers = malloc(d * sizeof(Persona));
	int corrette = 0;

	//ordina gli elementi del vettotr vect in base all'ordine alfabetico della persona presente nella foto
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (strcmp(vect[i].p_inside, vect[j].p_inside) < 0) {
				swap(&vect[i], &vect[j]);
			}
		}
	}

	//conteggia il numero di presenze dei soggetti nelle varie foto e crea un vettore vect_per nel quale salvare i dati acquisiti
	strcpy(pers_analisi, vect[0].p_inside);
	for (i = 0; i <= n; i++) {
		if ((strcmp(pers_analisi, vect[i].p_inside) == 0) && (strcmp(vect[i].p_riconosciuta, "ERRORE") != 0)) {
			count_pers++;	
		}
		if ((strcmp(pers_analisi, vect[i].p_inside) != 0) && (strcmp(vect[i].p_riconosciuta, "ERRORE") != 0)) {
			strcpy(vect_pers[n_persone].nome, pers_analisi);
			vect_pers[n_persone].frequenza = count_pers;
			n_persone++;
			strcpy(pers_analisi, vect[i].p_inside);
			count_pers = 1;
			if (n_persone >= d) {
				d = d + 2;
				vect_pers = realloc(vect_pers, d * sizeof(Persona));
			}
		}
	}

	//conta il numero di riconoscimenti corretti per ogni soggetto
	for (i = 0; i < n_persone; i++) {
		for (j = 0; j < n; j++) {
			if ((strcmp(vect[j].p_inside, vect[j].p_riconosciuta) == 0) && (strcmp(vect[j].p_inside, vect_pers[i].nome) == 0)) {
				corrette++;	
			}
		}
		
		vect_pers[i].ric_corretti = corrette;
		corrette = 0;
	}

	//calcola le percentuali delle presenze e dei riconoscimenti corretti per ogni soggetto
	for (i = 0; i < n_persone; i++) {
		vect_pers[i].perc_frequenza = (double)vect_pers[i].frequenza * 100 / (n - n_errori);
		vect_pers[i].perc_ric_corretti = (double)vect_pers[i].ric_corretti * 100 / vect_pers[i].frequenza;
	}

	//stampa i risultati
	for (i = 0; i < n_persone; i++) {
		printf("%s: %d immagini su %d (%lf), %d riconosciute correttamente (%lf)\n", vect_pers[i].nome, vect_pers[i].frequenza, n - n_errori, vect_pers[i].perc_frequenza, vect_pers[i].ric_corretti, vect_pers[i].perc_ric_corretti);
	}

	free(vect_pers);
}


void swap(Immagine *a, Immagine *b)
{
	Immagine tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}


int f_calc_area(int w, int h)
{
	//funzione per il calcolo dell'area espressa in numero di pixel
	return w * h;
}


void f_ordina_aree(Immagine *vect, int n)
{
	//funzione che riordina le righe del file di input in base alla misura dell'area, espressa in pixel, seguendo l'ordine crescente
	int i;
	int j;

	for (i = 0; i < n; i++) {
		for (j = i + 1; j < n; j++) {
			if (f_calc_area(vect[i].width, vect[i].height) > f_calc_area(vect[j].width, vect[j].height)) {
				swap(&vect[i], &vect[j]);
			}
		}
	}

	puts("\n[FILE DI OUTPUT]");
	for (i = 0; i < n; i++) {
		printf("%d %d %d %s %s\n", vect[i].id, vect[i].width, vect[i].height, vect[i].p_inside, vect[i].p_riconosciuta);
	}

}
