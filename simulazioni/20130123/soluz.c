#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<ctype.h>

#define D printf("%d\n", __LINE__);

struct materiali {
	char nome[40];
	double ps;
};

struct elenco {
	char nome[40];
	double v;
};

struct file_materiali {
	char nome_file[200];
	int n;
	struct materiali *m;
};

struct file_elenco {
	char nome_file[200];
	int n;
	struct elenco *el;
};

/* 
 * Caricamento dei dati contenuti nel file materiali.dat.
 */

int carica_materiali(struct file_materiali *fm)
{
	FILE *f;
	char buffer[200];
	int i;

	while ((f = fopen(fm->nome_file, "r")) == 0) {
		printf("Errore nell'apertura di %s\n", fm->nome_file);
		return 1;
	}

	fgets(buffer, sizeof(buffer), f);
	sscanf(buffer, "%d", &fm->n);
	fm->m = malloc(fm->n * sizeof(struct materiali));
	for (i = 0; i < fm->n; i++) {
		fgets(buffer, sizeof(buffer), f);
		sscanf(buffer, "%s %lf", fm->m[i].nome, &fm->m[i].ps);
	}

	return 0;
}

/* 
 * Caricamento dei dati contenuti nel file elencoX.dat.
 */

int carica_elenco(struct file_elenco *fe)
{
	FILE *f;
	char buffer[200];
	int i;

	while ((f = fopen(fe->nome_file, "r")) == 0) {
		printf("Errore nell'apertura di %s\n", fe->nome_file);
		return 1;
	}

	fgets(buffer, sizeof(buffer), f);
	sscanf(buffer, "%d", &fe->n);
	fe->el = malloc(fe->n * sizeof(struct elenco));
	for (i = 0; i < fe->n; i++) {
		fgets(buffer, sizeof(buffer), f);
		sscanf(buffer, "%s %lf", fe->el[i].nome, &fe->el[i].v);
	}

	return 0;
}

/* 
 * Funzione che calcola il peso totale dei materiali presenti in elencoX.dat.
 */

double peso_tot(struct file_materiali *fm, struct file_elenco *fe)
{
	int i, j;
	double p = 0;

	for (i = 0; i < fe->n; i++) {
		for (j = 0; j < fm->n; j++) {
			if (strcmp(fe->el[i].nome, fm->m[j].nome) == 0) {
				p += fe->el[i].v * fm->m[j].ps * 0.001;
			}
		}
	}

	return p;
}

/* 
 * Funzione che stampa i nomi dei materiali che iniziano con il carattere lett.
 */

int filtro(struct file_materiali *fm, char lett)
{
	int i;

	printf("I materiali che iniziano per %c sono:\n", toupper(lett));

	for (i = 0; i < fm->n; i++) {
		if (toupper(fm->m[i].nome[0]) == toupper(lett)) {
			printf("%s\n", fm->m[i].nome);
		}
	}

	return 0;
}

/*
 * Funzione di comparazione basata sul peso specifico
 * di due strutture di tipo struct materiali.
 */

int cmp_materiali(const void *c1p, const void *c2p)
{
	struct materiali *c1 = (struct materiali *)(c1p);
	struct materiali *c2 = (struct materiali *)(c2p);

	return (((c1->ps > c2->ps) - (c1->ps < c2->ps)));
}

/*
 * Ordinamento dell'elenco di materiali.
 */

void ordina_materiali(struct file_materiali *fm)
{
	qsort(fm->m, fm->n, sizeof(struct materiali), cmp_materiali);
}

/*
 * Visualizzazione dell'elenco di materiali.
 */

void stampa_materiali(struct file_materiali *fm)
{
	int i;

	printf("Elenco materiali ordinato:\n");

	for (i = 0; i < fm->n; i++) {
		printf("%s %f\n", fm->m[i].nome, fm->m[i].ps);
	}
}

int main(int argc, char *argv[])
{
	struct file_materiali fm;
	struct file_elenco fe;

	if (argc != 4) {
		printf("Uso: comando file_materiali file_elenco lettera\n");
		return -1;
	}

	strncpy(fm.nome_file, argv[1], sizeof(fm.nome_file));
	strncpy(fe.nome_file, argv[2], sizeof(fe.nome_file));

	if (carica_materiali(&fm) != 0)
		return 1;
	if (carica_elenco(&fe) != 0)
		return 2;

	/* 
	 * prima ordinamento e stampa, per agevolare la lettura
	 * delle altre informazioni
	 */
	ordina_materiali(&fm);
	stampa_materiali(&fm);

	printf("Peso totale = %lf\n", peso_tot(&fm, &fe));
	
	filtro(&fm, argv[3][0]);

	return 0;
}
