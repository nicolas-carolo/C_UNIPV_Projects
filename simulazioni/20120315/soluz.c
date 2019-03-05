#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
 * decommentare la seguente definizione di macro per avere la stampa
 * completa delle medie di entrata/uscita mensile, includendo cioe`
 * anche i mesi per i quali non ci sono entrate/uscite
 */
//#define STAMPA_TUTTO

/* 
 * per l'uso dell'indicizzazione dei vettori cosi` come fatta in questo
 * programma e` **indispensabile** conoscere l'intervallo degli anni
 * considerati; ma questa era una informazione esplicitamente fornita
 * nella traccia
 */
#define MINA   (1990)
#define MAXA   (2005)

struct record {
	int a, m, g;
	float amm;
};

/* 
 * stampa il nome di un mese a partire dal valore numerico
 * che lo identifica; una "finezza" non indispensabile
 */
void stampa_mese(char *s, int m)
{
	char *ms[12] = {"Gennaio", "Febbraio", "Marzo", "Aprile", "Maggio", "Giugno", "Luglio", "Agosto", "Settembre", "Ottobre", "Novembre", "Dicembre"};

	printf("%s %s\n", s, ms[m]);
}

int anno_maggiori_entrate(struct record *r, int n)
{
	float a[MAXA - MINA + 1] = {0.0}; 
	float max; 
	int i, anno;

	/* 
	 * si noti l'uso del valore dell'anno per indicizzare il vettore,
	 * opportunamente decrementato per rientrare nel corretto intervallo
	 */
	for (i = 0; i < n; i++) {
		if (r[i].amm > 0)
			a[r[i].a - MINA] += r[i].amm;
	}
	
	/* 
	 * viene cercato il massimo su tutti gli anni;
	 * il primo valore assegnato e` quello del primo anno;
	 * rimarra` tale se il massimo e` effettivamente totalizzato
	 * nel primo anno
	 */
	anno = MINA;
	max = a[0];
	for (i = 0; i <= (MAXA - MINA); i++) {
		if (a[i] > max) {
			max = a[i];
			anno = MINA + i;
		}
	}

	return anno;
}

int mese_maggiori_uscite(struct record *r, int n)
{
	float m[12] = {0.0}; 
	float max;
	int i, mese;

	for (i = 0; i < n; i++) {
		if (r[i].amm < 0)
			m[r[i].m - 1] -= r[i].amm;
	}

	mese = 0;
	max = m[0];
	for (i = 0; i < 12; i++) {
		if (m[i] > max) {
			max = m[i];
			mese = i;
		}
	}

	return mese;
}

void anni_saldo(struct record *r, int n, int *amin, int *amax)
{
	float a[MAXA - MINA + 1] = {0.0}; 
	float min, max;
	int i;

	for (i = 0; i < n; i++) {
		a[r[i].a - MINA] += r[i].amm;
	}
	
	*amin = MINA;
	*amax = MINA;
	max = a[0];
	min = a[0];
	for (i = 0; i <= (MAXA - MINA); i++) {
		if (a[i] > max) {
			max = a[i];
			*amax = MINA + i;
		}
		if (a[i] < min) {
			min = a[i];
			*amin = MINA + i;
		}
	}
}

/* 
 * per ogni mese bisogna calcolare la media, quindi bisogna tenere traccia 
 * della somma dell'ammontare e del numero di elementi sommati
 */
struct media {
	float somma;
	int n;
};

void media_entrate(struct record *r, int n)
{
	/*
	 * l'elemento [i][j] indica il j-esimo mese dell'i-esimo anno
	 */
	struct media ent[MAXA - MINA + 1][12] = {{{0.0, 0}}};
	struct media usc[MAXA - MINA + 1][12] = {{{0.0, 0}}};
	int i, j;

	/*
	 * calcola somme e divisori per ciascun mese
	 */
	for (i = 0; i < n; i++) {
		if (r[i].amm > 0) {
			ent[r[i].a - MINA][r[i].m - 1].somma += r[i].amm;
			ent[r[i].a - MINA][r[i].m - 1].n++;
		}
		if (r[i].amm < 0) {
			usc[r[i].a - MINA][r[i].m - 1].somma -= r[i].amm;
			usc[r[i].a - MINA][r[i].m - 1].n++;
		}
	}
	
	/* 
	 * nota: stampa solo se il divisore e` != 0
	 * nel caso sia definita la macro STAMPA_TUTTO
	 * stampa un messaggio per notificare che non ci sono
	 * entrate o uscite nel mese considerato
	 */
	for (i = 0; i <= (MAXA - MINA); i++) {
		for (j = 0; j < 12; j++) {
			if (ent[i][j].n) {
				printf("%02i/%i: media entrate %f\n", j + 1, MINA + i, ent[i][j].somma / ent[i][j].n);
			}
#ifdef STAMPA_TUTTO
			else {
				printf("%02i/%i: nessuna entrata\n", j + 1, MINA + i);
			}
#endif
			if (usc[i][j].n) {
				printf("%02i/%i: media uscite  %f\n", j + 1, MINA + i, usc[i][j].somma / usc[i][j].n);
			}
#ifdef STAMPA_TUTTO
			else {
				printf("%02i/%i: nessuna uscita\n", j + 1, MINA + i);
			}
#endif
		}
	}
}

/* 
 * funzione utilizzata dalla qsort:
 * confronta il valore dell'ammontare nelle due strutture;
 * il valore ritornato e` > 0 se c1->amm e` maggiore di c2->amm
 * e` < 0 se c1->amm e` minore di c2->amm
 * e vale 0 se sono uguali
 */
int cmp_amm(const void *c1p, const void *c2p)
{
	struct record *c1 = (struct record *)(c1p),
	              *c2 = (struct record *)(c2p);

	return (c1->amm - c2->amm);
}

void ordinamento(struct record *r, int n)
{
	int i;

	/*
	 * una volta implementata la corretta funzione di confronto,
	 * l'ordinamento si effettua con una semplice chiamata a qsort
	 */
	qsort(r, n, sizeof(struct record), cmp_amm);

	/* 
	 * per comodita` stampa a video invece che su file come richiesto
	 * nella traccia d'esame
	 */
	for (i = 0; i < n; i++) {
		printf("%d %02d %02d %f\n", r[i].a, r[i].m, r[i].g, r[i].amm);
	}
}

int main(int argc, char *argv[])
{
	int n, dim;
	struct record *r;
	char s[100];
	int amin, amax;

	dim = 1024;
	if (!(r = malloc(dim * sizeof(struct record)))) {
		perror("Errore allocazione memoria\n");
		return 1;
	}

	/* 
	 * per comodita` legge da standard input invece che da file;
	 * utilizzare la redirezione sulla linea di comando 
	 * per leggere da un file
	 */
	n = 0;
	while (fgets(s, sizeof(s), stdin)) {
		sscanf(s, "%d %2d %2d %f", &r[n].a, &r[n].m, &r[n].g, &r[n].amm);
		n++;

		/* 
		 * se si supera la dimensione del vettore 
		 * si raddoppia la dimensione e si rialloca un nuovo vettore
		 * di tale dimensione
		 */
		if (n >= dim) {
			dim *= 2;
			if (!(r = realloc(r, dim * sizeof(struct record)))) {
				perror("Errore allocazione memoria\n");
				return 1;
			}
		}
	}

	printf("Anno maggiori entrate: %i\n", anno_maggiori_entrate(r, n));
	
	stampa_mese("Mese maggiori uscite:", mese_maggiori_uscite(r, n));

	anni_saldo(r, n, &amin, &amax);
	printf("Anno miglior saldo: %i\n", amax);
	printf("Anno peggior saldo: %i\n", amin);

	media_entrate(r, n);

	ordinamento(r, n);

	free(r);

	return 0;
}
