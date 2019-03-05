#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SLASH 47	//valore intero corrispondente al carattere'/' (ASCII)
#define PUNTO 46	//valore intero corrispondente al carattere '.'

void tipo_percorso(char dir[]);
int find_basename_len_dirname(char dir[], int lunghezza);
void find_dirname(char dir[], int lunghezza_dirname);
void find_extension(char dir[], int lunghezza_dirname, int lunghezza);

int main(int argc, char *argv[])
{
	int lunghezza;
	int lunghezza_dirname;

	if (argc != 2) {
		puts("#ERRORE: Argomento non valido!");
		return 0;
	}
	
	//restituisce la lunghezza del percorso inserito
	lunghezza = strlen(argv[1]);

	//restituisce la lunghezza del dirname e stampa la base con la funzione dedicata
	lunghezza_dirname = find_basename_len_dirname(argv[1], lunghezza);
	puts("");
	
	//stampa il dirname chiamando la funzione dedicata
	find_dirname(argv[1], lunghezza_dirname);
	puts("");

	//chiama la funzione per la stampa del tipo di percorso
	tipo_percorso(argv[1]);
	puts("");
	
	//chiama la funzione per la stampa dell'estensione
	find_extension(argv[1], lunghezza_dirname, lunghezza);

	return 0;
}


void tipo_percorso(char dir[])
{

	puts("[TIPO]");

	if (dir[0] == SLASH) {	//se il primo carattere della stringa è '/' allora è assoluto
		puts("assoluto");
	}
	else {			//altrimenti è relativo
		puts("relativo");
	}

}


int find_basename_len_dirname(char dir[], int lunghezza)
{
	int i;
	int lunghezza_basename;
	int lunghezza_dirname;

	//ricerca la posizione dell'ultimo slash della stringa (quello che introduce il basename)
	i = lunghezza - 1;
	while (dir[i] != SLASH) {
		i--;

		if (i < 0) {	//se lo slash non viene trovato termina il ciclo
				break;
		}
	}

	lunghezza_basename = lunghezza - i - 1;
	lunghezza_dirname = lunghezza - lunghezza_basename;

	//vengono stampati i caratteri contenuti nel vettore dir[] a partire dalla prima lettera del basename
	puts("[BASENAME]");
	for (i = lunghezza_dirname; i < lunghezza; i++) {
	printf("%c", dir[i]);
	}
	puts("");

	return lunghezza_dirname; //restituisce alla funzione main la lunghezza del dirname
	

}


void find_dirname(char dir[], int lunghezza_dirname)
{
	int i;
	
	//stampa il vettore dir[] da dir[0] fino al carattere precedente all'ultimo slash
	puts("[DIRNAME]");
	for (i = 0; i < lunghezza_dirname - 1; i++) {
	printf("%c", dir[i]);
	}
	puts("");

}


void find_extension(char dir[], int lunghezza_dirname, int lunghezza)
{
	int i;
	int lunghezza_estensione;
	int lunghezza_no_ext;

	//ricerca l'ultimo punto all'interno del basename
	puts("[ESTENSIONE]");
	i = lunghezza - 1;
	while (dir[i] != PUNTO) {
		i--;

		if (i < lunghezza_dirname) {	//se la ricerca esce dal campo del basename termina la ricerca uscendo dal ciclo
				break;		//è il caso in cui il file non presenta un'estensione
		}
	}

	lunghezza_estensione = lunghezza - i - 1;
	lunghezza_no_ext = lunghezza - lunghezza_estensione;

	if (i < lunghezza_dirname) {		//nessuna estensione
			puts("nessuna");
	}
	else {					//stampa estensione
		for (i = lunghezza_no_ext; i < lunghezza; i++) {
		printf("%c", dir[i]);
		}
		puts("");
	}

}
