#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SLASH 47
#define PUNTO 46

void tipo_percorso(char dir[]);
int find_basename_len_dirname(char dir[], int lunghezza);
void find_dirname(char dir[], int lunghezza_dirname);
void find_extension(char dir[], int lunghezza_dirname, int lunghezza);
int control_slash(char dir[]);
void find_dirname_completo(char dir[], int lunghezza_dirname);

int main(int argc, char *argv[])
{
	int lunghezza;
	int lunghezza_dirname;
	int consecutive_slash;

	//controlla che ci sia un solo argomento inserito oltre al nome del programma
	if (argc != 2) {
		puts("#ERRORE: Argomento non valido!");
		return 0;
	}
	
	//misura la lunghezza della stringa
	lunghezza = strlen(argv[1]);

	//chiama la funzione per il controllo della presenza di due o più '/' consecutivi
	consecutive_slash = control_slash(argv[1]);

	//stampa il basename tramite l'apposita funzione che restituisce anche la lunghezza del dirname
	puts("[BASENAME]");
	lunghezza_dirname = find_basename_len_dirname(argv[1], lunghezza);
	puts("");
	
	//stampa il dirname chiamando la funzione dedicata
	puts("[DIRNAME]");
	find_dirname(argv[1], lunghezza_dirname);
	puts("");

	//stampa il tipo di percorso chiamando la funzione dedicata
	tipo_percorso(argv[1]);
	puts("");

	//stampa il tipo di estensione chiamando la funzione dedicata
	find_extension(argv[1], lunghezza_dirname, lunghezza);

	//stampa il dirname completo chiamando la stessa funzione che stampa il dirname
	puts("\n[DIRNAME_COMPLETO]");
	if (lunghezza_dirname == 0) {	//se non c'è il dirname si fa riferimento alla cartella corrente
		puts(".");
	}
	if (consecutive_slash == 1) { //se ci sono più '/' la cartella è comunque root
		puts("/");
	}
	else {				//CASO GENERALE: chiama la funzione dedicata
		find_dirname_completo(argv[1], lunghezza_dirname);
	}
	
	puts("\n[BASENAME_COMPLETO]");
	if (consecutive_slash == 0) {	//CASO GENERALE
		lunghezza_dirname = find_basename_len_dirname(argv[1], lunghezza);
	}
	else {				//se ci sono più '/' consecutivi il base name è '/'
		puts("/");
	}

	return 0;
}


void tipo_percorso(char dir[])
{

	puts("[TIPO]");

	if (dir[0] == SLASH) {	//se il percorso inizia con '/' allora è assoluto
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

	i = lunghezza - 1;

	if (dir[i] == SLASH && lunghezza == 1) {	//CASO INPUT: /
		printf("%c\n", dir[0]);
		return 2; //dirname = basename
	}

	if (dir[i] == SLASH && lunghezza > 1) {		//CASO '/' CONSECUTIVI SUPERFLUI A FINE PERCORSO:
		while (dir[i] == SLASH) {		//elimina gli '/' in eccesso
			lunghezza = lunghezza - 1;
			i--;
		}
	}

	i = lunghezza - 1;

	while (dir[i] != SLASH) {	//itera il processo per trovare la posizione dell'ultimo '/'
		i--;

		if (i < 0) {		//se non trova nessuno '/' termina il ciclo
			break;
		}
	}

	lunghezza_basename = lunghezza - i - 1;
	lunghezza_dirname = lunghezza - lunghezza_basename;

	for (i = lunghezza_dirname; i < lunghezza; i++) {	//stampa il basename a partire dal carattere
	printf("%c", dir[i]);					//dopo l'ultimo '/'
	}
	puts("");	

	return lunghezza_dirname;	//ritorna alla main la lunghezza del dirname
}


void find_dirname(char dir[], int lunghezza_dirname)
{
	int i;
	
	//stampa il dirname (caratteri da dir[0] all'ultimo '/' escluso
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

	puts("[ESTENSIONE]");
	
	i = lunghezza - 1;
	while (dir[i] != PUNTO) {	//cerca la posizione del punto all'interno del basename
		i--;

		if (i < lunghezza_dirname) {	//se non lo trova interrompe il ciclo
				break;
		}
	}

	lunghezza_estensione = lunghezza - i - 1;
	lunghezza_no_ext = lunghezza - lunghezza_estensione;

	//se il percorso contiene solo un '.' o '..' non c'è nessuna estensione
	if ((dir[0] == PUNTO && lunghezza == 1) || (dir[0] == PUNTO && dir[1] == PUNTO && lunghezza == 2)) {
		puts("nessuna");
	}
	//se non c'è un punto nel basename non c'è nessuna estensione
	if (i < lunghezza_dirname) {
		puts("nessuna");
	}
	//se c'è un punto all'interno del basename allora stampa la stringa a partire dal carattere
	//dopo il '.'
	else {
		for (i = lunghezza_no_ext; i < lunghezza; i++) {
		printf("%c", dir[i]);
		}
		puts("");
	}
}


int control_slash(char dir[])
{
	int i = 0;
	int count_slash = 0;

	while (dir[i] == SLASH) {
		count_slash++;
		i++;
	}

	if (count_slash > 1) {
		return 1;	//presenza di più slash consecutivi
	}
	else {
		return 0;	//nessuno o uno slash consecutivi
	}
}


void find_dirname_completo(char dir[], int lunghezza_dirname)
{
	int i;

	//CASO PARTICOLARE: se il percorso contiene solo il carattere '/' allora il dirname completo è '/'
	if (dir[0] == SLASH && lunghezza_dirname == 1) {
		puts("/");
	}
	//altrimenti processo analogo alla funzione find_dirname
	else {
		for (i = 0; i < lunghezza_dirname - 1; i++) {
		printf("%c", dir[i]);
		}
		puts("");
	}
}
