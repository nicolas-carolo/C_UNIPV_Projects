#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_PILOTI 20
#define N_TEAM 10

typedef struct {
	char nome[35];
	char team[20];
	int posizione;
} Input;

typedef struct {
	char nome[35];
	char team[20];
	int tot_punti;
} Pilota;

typedef struct {
	char nome[20];
	int tot_punti;
} Team;

void f_pilota_vincitore(Input *vect, int n, Pilota *vect_piloti);
void f_ordine_alfabetico_piloti(Pilota *vect_piloti);
void swap(Pilota *a, Pilota *b);
void f_squadra_vincitrice(Pilota *vect_piloti, Team *vect_team);
void f_ordine_alfabetico_piloti_per_squadre(Pilota *vect_piloti);

int main(int argc, char *argv[])
{
	char buf[55];
	FILE *fin;
	int d = 20;
	Input *vect = malloc(d * sizeof(Input));
	int pos = 1;
	int n_gare = 0;
	int n = 0;
	Pilota vect_piloti[N_PILOTI];
	Team vect_team[N_TEAM];

	if (argc != 2) {
		printf("#USO: %s input_file", argv[0]);
		return 1;
	}

	if (!(fin = fopen(argv[1], "r"))) {
		printf("#ERRORE: impossibile aprire il file \"%s\".", argv[1]);
		return -1;
	}

	//legge dal file di input e conteggia il numero di gare
	while (fgets(buf, sizeof(buf), fin)) {	
		sscanf(buf, "%s %s", vect[n].nome, vect[n].team);
		vect[n].posizione = pos;
		pos++; 
		n++;
		if ((n % N_PILOTI) == 0) {
			pos = 1;
			n_gare++;
			d = d + 20;
			vect = realloc(vect, d * sizeof(Input));
		}
	}

	//stampa il numero di gare
	printf("\n[NUMERO_GARE]\n%d\n", n_gare);

	f_pilota_vincitore(vect, n, vect_piloti);
	f_squadra_vincitrice(vect_piloti, vect_team);

	fclose(fin);
	free(vect);

	return 0;
}


void f_pilota_vincitore(Input *vect, int n, Pilota *vect_piloti)
{
	//funzione che stampa il nome del pilota vincitore e il suo punteggio totale
	int i;
	int j;
	int k;
	int punti[] = {25, 18, 15, 12, 10, 8, 6, 4, 2, 1};
	int i_max_punti;
	int punteggio_max = 0;
	int somma_punteggio = 0;

	//copia nel vettore vect_piloti i nomi dei piloti
	for (i = 0; i < N_PILOTI; i++) {
		strcpy(vect_piloti[i].nome, vect[i].nome);
		strcpy(vect_piloti[i].team, vect[i].team);
	}

	//calcola il punteggio totale per ogni giocatore e salva il totale negli appositi campi del vettore vect_piloti
	for (i = 0; i < N_PILOTI; i++) {
		for (j = 0; j < n; j++) {
			if (strcmp(vect_piloti[i].nome, vect[j].nome) == 0) {
				for (k = 0; k < 10; k++) {
					if ((vect[j].posizione < k + 2) && (vect[j].posizione > k)) {
						somma_punteggio = somma_punteggio + punti[k];
					}
				}	
			}
		}
		
		vect_piloti[i].tot_punti = somma_punteggio;
		somma_punteggio = 0;
	}

	//chiama la funzione dedicata al riordinamento degli elementi di un vettore in base all'ordine
	//alfabetico dei nomi dei piloti
	f_ordine_alfabetico_piloti(vect_piloti);

	//stabilisce qual è il pilota che ha ottenuto il maggior numero di punti
	for (i = 0; i < N_PILOTI; i++) {
		if (vect_piloti[i].tot_punti > punteggio_max) {
			punteggio_max = vect_piloti[i].tot_punti;
			i_max_punti = i;
		}
	}

	//stampa il risultato
	printf("\n[PILOTA_VINCITORE]\n%s %d\n", vect_piloti[i_max_punti].nome, punteggio_max);
}


void f_ordine_alfabetico_piloti(Pilota *vect_piloti)
{
	//funzione che ordina un vettore in base all'ordine alfabetico di nomi dei piloti
	int i;
	int j;

	for (i = 0; i < N_PILOTI; i++) {
		for (j = 0; j < N_PILOTI; j++) {
			if (strcmp(vect_piloti[i].nome, vect_piloti[j].nome) < 0) {
				swap(&vect_piloti[i], &vect_piloti[j]);
			}
		}
	}
}


void swap(Pilota *a, Pilota *b)
{
	Pilota tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}


void f_squadra_vincitrice(Pilota *vect_piloti, Team *vect_team)
{
	int i;
	int j = 0;
	int somma_punteggio = 0;
	int i_max_punti;
	int punteggio_max = 0;
	
	//chiamata alla funzione per riordinare un vettore in base all'ordine alfabetico delle squadre
	f_ordine_alfabetico_piloti_per_squadre(vect_piloti);

	//copia i nomi delle squdre nel vettore vect_team
	for (i = 0; i < N_TEAM; i++) {
		strcpy(vect_team[i].nome, vect_piloti[j].team);
		j = j + 2;
	}

	//esegue la somma dei punteggi delle squadre (due piloti per ogni squadra)
	for (i = 0; i < N_TEAM; i++) {
		for (j = 0; j < N_PILOTI; j++) {
			if (strcmp(vect_team[i].nome, vect_piloti[j].team) == 0) {
				somma_punteggio = somma_punteggio + vect_piloti[j].tot_punti;
			}
		}
	
		vect_team[i].tot_punti = somma_punteggio;
		somma_punteggio = 0;
	}

	//stabilisce qual è la squadra che ha totalizzato il punteggio migliore
	for (i = 0; i < N_TEAM; i++) {
		if (vect_team[i].tot_punti > punteggio_max) {
			punteggio_max = vect_team[i].tot_punti;
			i_max_punti = i;
		}
	}

	//stampa il risultato
	printf("\n[SQUADRA_VINCITRICE]\n%s %d\n", vect_team[i_max_punti].nome, punteggio_max);
}


void f_ordine_alfabetico_piloti_per_squadre(Pilota *vect_piloti)
{
	int i;
	int j;

	for (i = 0; i < N_PILOTI; i++) {
		for (j = 0; j < N_PILOTI; j++) {
			if (strcmp(vect_piloti[i].team, vect_piloti[j].team) < 0) {
				swap(&vect_piloti[i], &vect_piloti[j]);
			}
		}
	}

}
