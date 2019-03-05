#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_COLORI 4

typedef struct {
	char nome[30];
	char sesso;
	char colore[15];
	char madre[30];
	char colore_madre[15];
	char padre[30];
	char colore_padre[15];
	int numero_figli;
} Dati;

void f_conta_sesso(Dati *vect, int n);
void f_conta_colori(Dati *vect, int n);
void f_colore_diverso_da_genitori(Dati *vect, int n);
void f_prolifici(Dati *vect, int n);

int main(int argc, char *argv[])
{
	int n = 0;
	char buf[512];
	FILE *fin;
	int d = 10;
	Dati *vect = malloc(d * sizeof(Dati));

	if (argc != 2) {
		printf("USO: %s input_file\n", argv[0]);
		return 1;
	}

	if(!(fin = fopen(argv[1], "r"))) {
		return -1;
	}

	while (fgets(buf, sizeof(buf), fin)) {
		sscanf(buf, "%s %c %s %s %s", vect[n].nome, &vect[n].sesso, vect[n].colore, vect[n].madre, vect[n].padre);
		n++;
		
		if (n >= d) {
			d = d + 2;
			vect = realloc(vect, d * sizeof(Dati));
			if (vect == NULL) {	//se non e' possibile riallocare la memoria il programma termina
				puts("#ERRORE: impossibile allocare altro spazio dinamicamente!");
				return 1;
			}
		}
	}

	f_conta_sesso(vect, n);
	f_conta_colori(vect, n);
	f_colore_diverso_da_genitori(vect, n);
	f_prolifici(vect, n);

	fclose(fin);
	free(vect);

	return 0;
}


void f_conta_sesso(Dati *vect, int n)
{
	//conta quanti maschi e quante femmine ci sono nell'allevamento
	int i;
	int maschi = 0;
	int femmine = 0;

	for (i = 0; i < n; i++) {
		if (vect[i].sesso == 'M') {
			maschi++;	
		}
	}
	
	femmine = n - maschi;

	printf("[SESSI]\n%d\n%d\n", maschi, femmine);
}

void f_conta_colori(Dati *vect, int n)
{
	//stampa il colore più ricorrente
	int i;
	int j;
	int count_colore[N_COLORI] = {0};
	char *colore[] = {"fulvo", "grigio", "marrone", "nero"};
	int max_colore = count_colore[0];
	int i_max_colore;

	for (i = 0; i < N_COLORI; i++) {
		for (j = 0; j < n; j++) { 
			if (strcmp(vect[j].colore, colore[i]) == 0) {
				count_colore[i]++;
			}	
		}
	}

	for (i = 0; i < N_COLORI; i++) {
		if (count_colore[i] > max_colore) {
			i_max_colore = i;
			max_colore = count_colore[i];
		}
	}	

	printf("[COLORE]\n%s\n", colore[i_max_colore]);
}


void f_colore_diverso_da_genitori(Dati *vect, int n)
{
	//stampa il numero dei cani con un colore diverso da entrambi i genitori
	int i;
	int j;
	int *ver_madre = malloc(n * sizeof(int));
	int *ver_padre = malloc(n * sizeof(int));
	int diversi = 0;
	
	//imposta a zero i vettori ver_madre e ver_padre
	for (i = 0; i < n; i++) {
		ver_madre[i] = 0;	
	}
	for (i = 0; i < n; i++) {
		ver_padre[i] = 0;	
	}

	//controlla se la madre dell'i-esimo cane fa parte dell'allevamento
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (strcmp(vect[i].madre, vect[j].nome) == 0) {
				ver_madre[i]++;	//se c'e' la madre = 1
				strcpy(vect[i].colore_madre, vect[j].colore);
			}
		}
	}

	//controlla se il padre dell'i-esimo cane fa parte dell'allevamento
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (strcmp(vect[i].padre, vect[j].nome) == 0) {
				ver_padre[i]++;	//se c'e' il padre = 1
				strcpy(vect[i].colore_padre, vect[j].colore);
			}
		}
	}

	//incerementa il numero dei diversi se l'i-esimo cane ha la madre e un colore diverso dalla madre e in più ha il padre e un colore diverso dal padre
	for (i = 0; i < n; i++) {
		if ((ver_madre[i] == 1 && strcmp(vect[i].colore, vect[i].colore_madre) != 0) && (ver_padre[i] == 1 && strcmp(vect[i].colore, vect[i].colore_padre) != 0)) {
			diversi++;	
		}
	}

	printf("\n[DIVERSI]\n%d\n", diversi);
	
	free(ver_madre);
	free(ver_padre);
}

void f_prolifici(Dati *vect, int n)
{
	//stampa in ordine alfabetico i nomi dei cani (maschi e femmine) che hanno avuto più di 7 figli
	int i;
	int j;

	//conta il numero di figli per ogni cagna
	for (i = 0; i < n; i++) {
		vect[i].numero_figli = 0;
		for (j = 0; j < n; j++) {
			if (strcmp(vect[i].nome, vect[j].madre) == 0) {
				vect[i].numero_figli++;
			}
		}
	}

	//conta il numero di figli per ogni cane
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (strcmp(vect[i].nome, vect[j].padre) == 0) {
				vect[i].numero_figli++;	
			}
		}
	}

	//stampa il nome del cane se e solo se esso/a ha avuto più di 7 figli
	puts("[PROLIFICI]");
	for (i = 0; i < n; i++) {
		if (vect[i].numero_figli > 7) {
			printf("%s\n",vect[i].nome);
		}
	}
}
