#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_TIRATORI 8
#define N_TIRI 15
#define RAGGIO_CENTRO 30

typedef struct {
	char nome[100];
	int totale_punti;
	double media;
	int dist_max;
	int dist_min;
	int tiri_centro;
} Dati;

int f_punteggio_totale(int vect_distanze[]);
double f_media(int vect_distanze[]);
int f_distanza_max(int vect_distanze[]);
void f_dist_max_assoluta(Dati *vect_dati);
int f_distanza_min(int vect_distanze[]);
void f_dist_min_assoluta(Dati *vect_dati);
int f_numero_tiri_centro(int vect_distanze[]);
void f_tiratori_migliori(Dati *vect_dati);
void f_print_classifica(Dati *vect_dati);
void swap(Dati *a, Dati *b);

int main(int argc, char *argv[])
{
	char buf[100];
	FILE *fin;
	int i;
	int j;
	int vect_distanze[N_TIRI];
	Dati vect_dati[N_TIRATORI];
 
	if (argc != 2) {
		printf("USO: %s input_file\n", argv[0]);
		return 1;
	}

	if (!(fin = fopen(argv[1], "r"))) {
		return -1;
	}

	
	for (i = 0; i < N_TIRATORI; i++) {
		fgets(buf, sizeof(buf), fin);
		strcpy(vect_dati[i].nome, buf);
		for (j = 0; j < N_TIRI; j++) {
			fgets(buf, sizeof(buf), fin);
			sscanf(buf, "%d", &vect_distanze[j]);
		}
		//func calcolo punteggio
		vect_dati[i].totale_punti = f_punteggio_totale(vect_distanze);
		//func calcolo media
		vect_dati[i].media = f_media(vect_distanze);
		//func dist max e min
		vect_dati[i].dist_min = f_distanza_min(vect_distanze);
		vect_dati[i].dist_max = f_distanza_max(vect_distanze);
		//func numero tiri al centro
		vect_dati[i].tiri_centro = f_numero_tiri_centro(vect_distanze);
	}

	f_tiratori_migliori(vect_dati);

	puts("[MINMAX]");
	f_dist_min_assoluta(vect_dati);
	f_dist_max_assoluta(vect_dati);

	puts("[MEDIA]");
	for (i = 0; i < N_TIRATORI; i++) {
		printf("%.1lf %s\n", vect_dati[i].media, vect_dati[i].nome);
	}

	f_print_classifica(vect_dati);

	fclose(fin);
	return 0;
}


int f_punteggio_totale(int vect_distanze[]) //da rivedere
{
	//funzione che dati i valori ricevuti corrispondenti alle distanze in millimetri dei 15 tiri di un tiratore,
	//restituisce alla funzione chiamante il punteggio totale del giocatore
	int i;
	int j;
	int distanze[7] = {150, 130, 110, 90, 70, 50, 30};
	int punti[7] = {1, 2, 3, 5, 7, 10, 15};
	int totale = 0;
	int punti_parziali;
	
	for (i = 0; i < N_TIRI; i++) {
		punti_parziali = 0;
		for (j = 0; j < 7; j++) {
			if (vect_distanze[i] <= distanze[j]) {
				punti_parziali = punti[j]; 
			}
		}
		totale = totale + punti_parziali;
	}
	
	return totale;
}


double f_media(int vect_distanze[])
{
	//funzione che dati i valori ricevuti corrispondenti alle distanze in millimetri dei 15 tiri di un tiratore,
	//restituisce alla funzione chiamante la media della distanza dal centro del bersaglio
	int i;
	int somma = 0;
	double media;

	for (i = 0; i < N_TIRI; i++) {
		somma = somma + vect_distanze[i];
	}

	media = ((double)somma / N_TIRI);
	return media;
}


int f_distanza_max(int vect_distanze[])
{
	//funzione che dati i valori ricevuti corrispondenti alle distanze in millimetri dei 15 tiri di un tiratore,
	//restituisce alla funzione chiamante il valore corrispondente al tiro più lontano dal centro di ogni tiratore
	int i;
	int max = 0;

	for (i = 0; i < N_TIRI; i++) {
		if (vect_distanze[i] > max) {
			max = vect_distanze[i];
		}
	}
	
	return max;
}


int f_distanza_min(int vect_distanze[])
{
	//funzione che dati i valori ricevuti corrispondenti alle distanze in millimetri dei 15 tiri di un tiratore,
	//restituisce alla funzione chiamante il valore corrispondente al tiro più vicino al centro di ogni tiratore
	int i;
	int min = vect_distanze[0];

	for (i = 0; i < N_TIRI; i++) {
		if (vect_distanze[i] < min) {
			min = vect_distanze[i];
		}
	}
	
	return min;
}


void f_dist_max_assoluta(Dati *vect_dati)
{
	//funzione che stampa a video la massima distanza dal centro in assoluto
	int i;
	int max = 0;

	for (i = 0; i < N_TIRATORI; i++) {
		if (vect_dati[i].dist_max > max) {
			max = vect_dati[i].dist_max;
		}
	}

	printf("%d\n", max);
}


void f_dist_min_assoluta(Dati *vect_dati)
{
	//funzione che stampa a video la minima distanza dal centro in assoluto
	int i;
	int min = vect_dati[0].dist_min;

	for (i = 1; i < N_TIRATORI; i++) {
		if (vect_dati[i].dist_min < min) {
			min = vect_dati[i].dist_min;
		}
	}

	printf("%d\n", min);
}


int f_numero_tiri_centro(int vect_distanze[])
{
	//funzione che dati i valori ricevuti corrispondenti alle distanze in millimetri dei 15 tiri di un tiratore,
	//restituisce alla funzione chiamante il valore corrispondente al numero di tiri andati a segno nella zona
	//più centrale di ogni singolo giocatore
	int i;
	int count_centri = 0;
	
	for (i = 0; i < N_TIRI; i++) {
		if (vect_distanze[i] <= RAGGIO_CENTRO) {
			count_centri++;
		}
	}

	return count_centri;
}


void f_tiratori_migliori(Dati *vect_dati)
{
	//funzione che stampa a video il nome del tiratore che ha centrato più volte la zona centrale del bersaglio
	int i;
	int j;
	int i_max[N_TIRATORI] = {0};
	int max = vect_dati[0].tiri_centro;

	for (i = 0; i < N_TIRATORI; i++) {
		if (vect_dati[i].tiri_centro > max) {
			i_max[i] = 1;
			max = vect_dati[i].tiri_centro;
			for (j = 0; j < i; j++) {
				i_max[j] = 0;
			}
		}
		if (vect_dati[i].tiri_centro == max) {
			i_max[i] = 1;
		}
	} 

	puts("[MAXCENTRI]");
	for (i = 0; i < N_TIRATORI; i++) {
		if (i_max[i] == 1) {
			printf("%s\n", vect_dati[i].nome);
		}
	}
	puts("");
}


void f_print_classifica(Dati *vect_dati)
{
	//funzione che stampa a video la classifica dal primo all'ultimo
	//questa perticolare funzione si serve dell'algoritmo denominato "bubblesort" per l'ordinamento dei dati
	//in ordine decrescente
	int i;
	int j;

	for (i = 0; i < N_TIRATORI; i++) {
		for (j = 0; j < N_TIRATORI; j++) {
			if (vect_dati[i].totale_punti > vect_dati[j].totale_punti) {
				//chiamata alla funzione swap per il riordinamento dei dati
				swap(&vect_dati[i], &vect_dati[j]);
			}
		}
	}

	puts("[CLASSIFICA]");
	for (i = 0; i < N_TIRATORI; i++) {
		printf("%d %s\n", vect_dati[i].totale_punti, vect_dati[i].nome);
	}


}


void swap(Dati *a, Dati *b)
{
	//funzione per scambiare di posizione due valori
	Dati tmp;
	
	tmp = *a;
	*a = *b;
	*b = tmp;
}
