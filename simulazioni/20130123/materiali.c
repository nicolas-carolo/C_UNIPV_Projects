#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
	char mat[100];	//tipo di materiale (es. argento, oro,..)
	double ps;	//peso specifico espresso in kg/m^3
} Materiale;

typedef struct {
	char mat[100];	//tipo di materiale (es. argento, oro,..)
	double volume;	//volume espresso in dm^3
	double peso;
	double ps;
} Elenco;

void f_peso_totale(Materiale *vect_mat, Elenco *vect_elenco, int n_materiali, int n_elenco);
void f_elenco_materiali_filtro_iniziale(Materiale *vect_mat, int n_materiali);
void f_ordina_mat_ps_crescente(Materiale *vect_mat, int n_materiali);
void swap(Materiale *a, Materiale *b);

int main(int argc, char *argv[])
{
	FILE *fin;
	Materiale *vect_mat;
	Elenco *vect_elenco;
	int n_materiali;
	int n_elenco;
	int i;
	char buf[256];

	if (argc != 3) {
		printf("USO: %s input_file_materiali input_file_elenco\n", argv[0]);
		return 1; 
	}

	if (!(fin = fopen(argv[1], "r"))) {
		printf("ERRORE: impossibile aprire il file di input \"%s\"\n", argv[1]);
		return -1;
	}

	//lettura materiali...
	n_materiali = atoi(fgets(buf, sizeof(buf), fin));

	vect_mat = malloc(n_materiali * sizeof(Materiale));

	for (i = 0; i < n_materiali; i++) {
		fgets(buf, sizeof(buf), fin);
		sscanf(buf, "%s %lf", vect_mat[i].mat, &vect_mat[i].ps);
	}

	fclose(fin);

	//lettura elenco...
	if (!(fin = fopen(argv[2], "r"))) {
		printf("ERRORE: impossibile aprire il file di input \"%s\"\n", argv[2]);
		return -1;
	}

	n_elenco = atoi(fgets(buf, sizeof(buf), fin));

	vect_elenco = malloc(n_elenco * sizeof(Elenco));

	for (i = 0; i < n_elenco; i++) {
		fgets(buf, sizeof(buf), fin);
		sscanf(buf, "%s %lf", vect_elenco[i].mat, &vect_elenco[i].volume);
	}

	fclose(fin);

	f_peso_totale(vect_mat, vect_elenco, n_materiali, n_elenco);
	f_elenco_materiali_filtro_iniziale(vect_mat, n_materiali);
	f_ordina_mat_ps_crescente(vect_mat, n_materiali);
	
	free(vect_mat);
	free(vect_elenco);
	return 0;
}


void f_peso_totale(Materiale *vect_mat, Elenco *vect_elenco, int n_materiali, int n_elenco)
{
	//funzione che stampa a video i materiali contenuti nel file di elenco con il relativo peso totale
	int i;
	int j;

	//aggiunge il campo relativo al peso specifico nella struttura Elenco
	for (i = 0; i < n_elenco; i++) {
		for (j = 0; j < n_materiali; j++) {
			if (strcmp(vect_elenco[i].mat, vect_mat[j].mat) == 0) {
				vect_elenco[i].ps = vect_mat[j].ps;
			}
		}
	}

	//stampa il peso totale
	puts("\n[PESO_TOTALE]");
	for (i = 0; i < n_elenco; i++) {
		vect_elenco[i].peso = (vect_elenco[i].volume / 1000) * vect_elenco[i].ps; //dm^3 -> m^3
		printf("%s %.3lf kg\n", vect_elenco[i].mat, vect_elenco[i].peso);
	}

}


void f_elenco_materiali_filtro_iniziale(Materiale *vect_mat, int n_materiali)
{
	//funzione che stampa a video i materiali che iniziano con la lettera inserita dall'utente 
	int i;
	char buf[1024];
	char filtro;

	puts("\nInserire una lettera per visualizzare un elenco di materiali filtrato in base alla lettera iniziale:");
	fgets(buf, sizeof(buf), stdin);
	filtro = toupper(buf[0]);

	puts("\n[ELENCO_FILTRATO]");
	for (i = 0; i < n_materiali; i++) {
		if(vect_mat[i].mat[0] == filtro) {
			printf("%s\n", vect_mat[i].mat);
		}
	}
}


void f_ordina_mat_ps_crescente(Materiale *vect_mat, int n_materiali)
{
	//funzione che stampa a video i materiali ordinati in ordine crescente in base al loro peso specifico
	int i;
	int j;

	for (i = 0; i < n_materiali; i++) {
		for (j = i + 1; j < n_materiali; j++) {
			if (vect_mat[i].ps > vect_mat[j].ps) {
				swap(&vect_mat[i], &vect_mat[j]); 
			}
		}
	}

	puts("\n[ELENCO_ORDINATO]");
	for (i = 0; i < n_materiali; i++) {
		printf("%s %lf\n", vect_mat[i].mat, vect_mat[i].ps);
	}
}


void swap(Materiale *a, Materiale *b)
{
	Materiale tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
