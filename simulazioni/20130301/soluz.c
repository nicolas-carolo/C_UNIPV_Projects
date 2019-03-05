#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Struttura che memorizza i record letti da file.
 */
struct record {
	int id;
	int h, w;
	char s1[200];
	char s2[200];
};

/*
 * Vettore che contiene i nomi dei partecipanti all'esperimento.
 * Se in un altro esperimento cambiano le persone coinvolte, o
 * ne cambia il numero, basta modificare appropriatamente questo
 * vettore per adattare il programma.
 * Quindi questo vettore e` l'unico "oggetto" da modificare per
 * adattare il programma ad esperimenti con persone diverse.
 */
char *nome[] = {"Anna", "Agnese", "Elvira", "Sara", "Giovanna", "Viola", "Alba"};

/*
 * Numero di partecipanti al progetto
 * NOTA: il numero viene dedotto dalla dimensione del vettore
 * e da quelle di un puntatore a char). In questo modo la
 * dichiarazione non cambia anche se si modifica il contenuto
 * del vettore nome.
 */
int nnomi = sizeof(nome) / sizeof(char *);

/*
 * Funzione di comparazione utilizzata da qsort.
 * Viene comparato il prodotto h*w di due strutture, che
 * corrisponde al numero di pixel della relativa immagine.
 */
int cmp_record(const void *c1p, const void *c2p)
{
  struct record *c1 = (struct record *)(c1p),
      *c2 = (struct record *)(c2p);

  return ((c1->w * c1->h) - (c2->w * c2->h));
}

/*
 * Stampa di tutto il contenuto del vettore.
 * Da utilizzare per riversare il vettore ordinato su file,
 * ma anche in fase di debug per verificare la correttezza del
 * caricamento dati.
 */
void stampa(struct record *rec, int n, FILE *f)
{
	int i;

	for (i = 0; i < n; i++) {
		fprintf(f, "%d %d %d %s %s (%d)\n",
				(rec + i)->id,
				(rec + i)->h,
				(rec + i)->w,
				(rec + i)->s1,
				(rec + i)->s2,
				(rec + i)->h * (rec + i)->w);   /* Per debug */
	}
}

/*
 * Funzione che analizza il vettore completamente caricato per
 * trovare le statistiche per persona.
 */
int analisi(struct record *rec, int n, int nc, int nerr)
{
	int *nn;    /* Numero di occorrenze di un nome */
	int *nnc;   /* Numero di riconoscimenti corretti per la persona */
	int i, j;

	/* 
	 * Alloca due vettori, dal momento che le statistiche
	 * sono "per persona"
	 */
	if (!(nn = malloc(nnomi * sizeof(int))))
		return 1;
	if (!(nnc = malloc(nnomi * sizeof(int)))) {
		free(nn);
		return 1;
	}

	/* Azzera i valori iniziali dei contatori */
	for (j = 0; j < nnomi; j++) {
		nn[j] = 0;
		nnc[j] = 0;
	}

	for (i = 0; i < n; i++) {
		if (strcmp((rec + i)->s2, "ERRORE")) {
			for (j = 0; j < nnomi; j++) {
				if (!strcmp((rec + i)->s1, nome[j])) {
					nn[j]++;
					if (!strcmp((rec + i)->s1, (rec + i)->s2)) {
						nnc[j]++;
					}
				}
			}
		}
	}

	/* Stampa le statistiche ottenute */
	for (j = 0; j < nnomi; j++) {

		/* 
		 * Le due stringhe costanti sono concatenate dal compilatore.
		 * Scritto in questo modo per estetica del sorgente.
		 */
		printf("%s: %d immagini su %d (%f%%), "
				"%d riconosciute correttamente (%f%%)\n",
				nome[j],
				nn[j],
				n - nerr,
				(float)(nn[j])/(n- nerr)*100,
				nnc[j],
				(float)(nnc[j])/nn[j]*100);
	}

	free(nn);
	free(nnc);

	return 0;
}

int main()
{
	struct record *rec;
	char buf[1000];
	int i = 0;
	int n;          /* Numero totale di record */
	int nerr = 0;   /* Numero totale di record con errore */
	int nc = 0;     /* Numero totale di riconoscimenti corretti */

	/* Lettura del numero di record nel file */
	fgets(buf, sizeof(buf), stdin);
	sscanf(buf, "%d", &n);

	/* Allocazione del vettore di strutture */
	if (!(rec = malloc(n * sizeof(struct record)))) {
		printf("Errore nell'allocazione della memoria\n");
		return -1;
	}

	/* 
	 * Ciclo di lettura.
	 * Alcune statistiche vengono calcolate un questa fase.
	 * Nel test del while viene controllato precauzionalmente
	 * che il numero di record letti non sia maggiore di quello
	 * previsto e per cui e` stato allocato il vettore di strutture.
	 */
	while (fgets(buf, sizeof(buf), stdin) && (i < n)) {
		sscanf(buf, "%d %d %d %s %s",
			&((rec + i)->id),
			&((rec + i)->h),
			&((rec + i)->w),
			(rec + i)->s1,
			(rec + i)->s2);

		/* Numero di riconoscimenti con ERRORE */
		if (!strcmp((rec + i)->s2, "ERRORE")) {
			nerr++;
		}

		/* Numero totale di riconoscimenti corretti */
		if (!strcmp((rec + i)->s1, (rec + i)->s2)) {
			nc++;
		}
		i++;
	}
	printf("%d riconoscimenti errati su %d (%f%%)\n",
			nerr, n, (float)(nerr)/n*100);
	printf("%d immagini riconosciute correttamente su %d (%f%%)\n",
			nc, n - nerr, (float)(nc)/(n - nerr)*100);

	/* Ordinamento di n elementi del vettore rec */
	qsort(rec, n, sizeof(struct record), cmp_record);

	if (analisi(rec, n, nc, nerr)) {
		printf("Errore nella funzione di analisi\n");
		return -1;
	}

	/* 
	 * Output su stdout per comodita`; la modifica per stampare
	 * su file come richiesto dalla traccia e` lasciata al
	 * lettore
	 */
	stampa(rec, n, stdout);

	free(rec);

	return 0;
}
