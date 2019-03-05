#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
	char stringa[55];
	int n_vocali;
	int n_parole;
} Strdat;

void f_vocali(Strdat *vect, int n);
void f_min_maxvocali(Strdat *vect, int n);
void f_inversione_caratteri(Strdat *vect, int n);
int len_count(char *s);
void f_word_count(Strdat *vect, int n);
void f_marcatura(Strdat *vect, int n);

int main(int argc, char *argv[])
{
	FILE *fin;
	char buf[55];
	int n = 0;
	int d = 10;
	Strdat *vect = malloc(d * sizeof(Strdat));

	if (argc != 2) {
		printf("#USO: %s input_file\n", argv[0]);
		return 0;
	}

	if (!(fin = fopen(argv[1], "r"))) {
		printf("#ERRORE: il file di input \"%s\" non e'stato trovato.\n", argv[1]);
		return 0;
	}

	while (fgets(buf, sizeof(buf), fin)) {
		strcpy(vect[n].stringa, buf);

		n++;

		if (n >= d) {
			d = d + 2;
			vect = realloc(vect, d * sizeof(Strdat));
			if (vect == NULL) {
				return 0;
			}
		}
	}

	f_vocali(vect, n);
	f_min_maxvocali(vect, n);
	f_inversione_caratteri(vect, n);
	f_word_count(vect, n);
	f_marcatura(vect, n);

	fclose(fin);
	free(vect);
	return 0;
}


void f_vocali(Strdat *vect, int n)
{
	//funzione che stampa a video il numero di vocali per ogni stringa
	char str_analisi[55];
	int i = 0;
	int j = 0;
	int k = 0;
	int count_vocali = 0;

	for (i = 0; i < n; i++) {
		strcpy(str_analisi, vect[i].stringa);
		k = 0;
		while (str_analisi[k] != '\n') {
			str_analisi[k] = tolower(str_analisi[k]);
			k++;
		}

		j = 0;
		while (str_analisi[j] != '\n') {
			if ((str_analisi[j] == 'a') || (str_analisi[j] == 'e') || (str_analisi[j] == 'i') ||(str_analisi[j] == 'o') ||(str_analisi[j] == 'u')) {
				count_vocali++;
			}
			j++;
		}
	
		vect[i].n_vocali = count_vocali;
	
		count_vocali = 0;
	}

	puts("[VOCALI]");
	for (i = 0; i < n; i++) {
		printf("%d\n", vect[i].n_vocali);
	}

}


void f_min_maxvocali(Strdat *vect, int n)
{
	//funzione che stampa a video rispettivamente la stringa con il minor numero di vocali e quella con il
	//maggior numero di vocali
	int i;
	int i_max;
	int i_min;
	int max_vocali = 0;
	int min_vocali = vect[0].n_vocali;

	for (i = 0; i < n; i++) {
		if (vect[i].n_vocali >= max_vocali) {
			max_vocali = vect[i].n_vocali;
			i_max = i;
		}
	}

	for (i = 0; i < n; i++) {
		if (vect[i].n_vocali <= min_vocali) {
			min_vocali = vect[i].n_vocali;
			i_min = i;
		}
	}

	printf("\n[MINMAX-VOCALI]\n%s%s", vect[i_min].stringa, vect[i_max].stringa);
}


void f_inversione_caratteri(Strdat *vect, int n)
{
	//funzione che stampa a video le stringhe inverite
	int len;
	int i;
	int j;
	
	printf("\n[INVERSIONE-CARATTERI]\n");
	for (i = 0; i < n; i++) {
		len = len_count(vect[i].stringa);
		for (j = len; j > -1; j--) {
			printf("%c",vect[i].stringa[j]);
		}
	}

	puts("");	
}


int len_count(char *s)
{
	//funzione che passa alla funzione chiamante il valore che corrisponde alla stringa
	//che le viene passata come parametro
	int i = 0;

	while (s[i] != '\n') {
		i++;
	}

	return i;
}


void f_word_count(Strdat *vect, int n)
{
	//funzione che conta il numero delle parole per ogni stringa
	//n°parole = n°spazi + 1
	//per questo motivo word_count è inizializzato a 1
	int len;
	int i;
	int j;
	int word_count = 1;
	
	printf("[PAROLE]\n");
	for (i = 0; i < n; i++) {
		len = len_count(vect[i].stringa);
		for (j = 0; j < len; j++) {
			if (vect[i].stringa[j] == 32) {
				word_count++;
			}
		}
		printf("%d\n", word_count);
		word_count = 1;
	}
}


void f_marcatura(Strdat *vect, int n)
{
	//funzione che sostituisce tutti i caratteri uguali al carattere di inizio stringa con il carattere '.'
	int len;
	int i;
	int j;
	char str_marcatura[55];
	char marcatura;
	
	printf("\n[MARCATURA]\n");
	for (i = 0; i < n; i++) {
		len = len_count(vect[i].stringa);
		marcatura = vect[i].stringa[0];
		strcpy(str_marcatura, vect[i].stringa);
		for (j = 0; j < len; j++) {
			if (str_marcatura[j] == marcatura) {
				str_marcatura[j] = '.';
			}
		}
		printf("%s", str_marcatura);
	}
}
