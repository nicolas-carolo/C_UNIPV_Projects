#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SOGLIA_32 32
#define N_MESI 12
#define N_CENTRALINE 10

typedef struct {
	int anno;
	int mese;
	int giorno;
	char id[10];
	double temp;
} Misura;

void f_maggiore_di_32(Misura *vect, int n);
void f_media(Misura *vect, int n);
void f_temp_max_min(Misura *vect, int n);
void f_mese_maggiori_acquisizioni(Misura *vect, int n);
void f_numero_centraline(Misura *vect, int n);

int main(int argc, char *argv[]){
	int d = 10;
	Misura *vect = malloc (d * sizeof(Misura));
	FILE *fin;
	int n = 0;
	char buf[200];

	if (argc != 2) {
		printf("USO: %s input_file\n", argv[0]);
		return 1;
	}

	if (!(fin = fopen(argv[1], "r"))) {
		return -1;
	}

	while (fgets(buf, sizeof(buf), fin)) {
		sscanf(buf, "%d-%d-%d %*d:%*d %s %lf", &vect[n].anno, &vect[n].mese, &vect[n].giorno, vect[n].id, &vect[n].temp);
		n++;
		if (n > d) {
			d = d + 2;
			vect = realloc(vect, d * sizeof(Misura));
			if (vect == NULL) {	//se non e' possibile riallocare la memoria il programma termina
				puts("ERRORE: impossibile allocare altro spazio dinamicamente!");
				return 1;
			}
		}
	}

	f_maggiore_di_32(vect, n);
	f_media(vect, n);
	f_temp_max_min(vect, n);
	f_mese_maggiori_acquisizioni(vect, n);
	f_numero_centraline(vect, n);
	
	return 0;
}


void f_maggiore_di_32(Misura *vect, int n)
{
	//funzione che stampa a video quante volte viene superata (o raggiunta) la temperatura di 32 gradi
	int i;
	int sup = 0;

	for (i = 0; i < n; i++) {
		if (vect[i].temp >= SOGLIA_32) {
			sup++;
		}
	}

	printf("[SUPERAMENTI]\n%d\n", sup);
}


void f_media(Misura *vect, int n)
{
	//funzione che stampa a video la media di tutte le misurazioni effettuate
	int i;
	double somma = 0;
	double media;

	for (i = 0; i < n; i++) {
		somma = somma + vect[i].temp;
	}

	media = (double)somma / n;

	printf("\n[MEDIA]\n%lf\n", media);
}


void f_temp_max_min(Misura *vect, int n)
{
	//funzione che stampa a video la minina e la massima registrate
	int i;
	int i_max;
	int i_min;
	double temp_max;
	double temp_min;

	temp_max = vect[0].temp;
	i_max = 0;
	temp_min = vect[0].temp;
	i_min = 0;

	for (i = 0; i < n; i++) {
		if (vect[i].temp < temp_min) {
			temp_min = vect[i].temp;
			i_min = i;
		}	
	}

	for (i = 0; i < n; i++) {
		if (vect[i].temp > temp_max) {
			temp_max = vect[i].temp;
			i_max = i;
		}	
	}

	puts("\n[MIN-MAX]");
	printf("%d-%02d-%02d %lf\n", vect[i_min].anno, vect[i_min].mese, vect[i_min].giorno, vect[i_min].temp);
	printf("%d-%02d-%02d %lf\n", vect[i_max].anno, vect[i_max].mese, vect[i_max].giorno, vect[i_max].temp);
}


void f_mese_maggiori_acquisizioni(Misura *vect, int n)
{
	//funzione che stampa a video il numero del mese con il maggior numero di misurazioni
	int i;
	int j;
	int count[N_MESI];
	int max_count = 0;
	int mese_max_test;

	for (i = 0; i < N_MESI; i++) {
		for (j = 0; j < n; j++) {
			if (j == vect[i].mese) {
				count[i + 1]++;	
			}
		}
	}

	for (i = 1; i <= N_MESI; i++) {
		if (count[i] > max_count) {
			max_count = count[i];
			mese_max_test = i;
		}
	}

	printf("\n[MESE]\n%d\n", mese_max_test);
}


void f_numero_centraline(Misura *vect, int n)
{
	//funzione che stampa a video il numero delle centraline che hanno svolto almeno una misurazione
	int i;
	int j;
	int numero_centraline = 1;
	int diverso = 0;
	char vect_centraline[N_CENTRALINE][10]; //vettore di stringhe con 10 caratteri ciascuna

	strcpy(vect_centraline[0], vect[0].id);

	for (i = 1; i < n; i++) {
		for (j = 0; j < N_CENTRALINE; j++) {
			if (strcmp(vect[i].id, vect_centraline[j]) != 0) {
				diverso++;
			}
		}
		if (diverso == N_CENTRALINE) {
			strcpy(vect_centraline[numero_centraline], vect[i].id);
			numero_centraline++;
		}
	
		diverso = 0;
	}

	printf("\n[NUM-CENTRALINE]\n%d\n", numero_centraline);	
}
