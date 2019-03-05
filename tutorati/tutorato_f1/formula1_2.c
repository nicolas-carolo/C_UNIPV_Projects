#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_PILOTI 20
#define N_GARE n_righe / 20
#define N_TEAM 10

typedef struct {
	char pilota[40];
	int punteggio;
	char team[40];
} Dati;

int f_numero_gare(int n_righe);
void f_pilota_vincitore(int n_righe, FILE *fin);
void f_team_vincitore(Dati classifica[], int n_righe, FILE *fin);
void f_team_vincitore_gara_singola(Dati vect[], FILE *fin);

int main(int argc, char *argv[])
{
	char buf[300];
	int n_righe = 0;
	FILE *fin;
	
	//se ci sono più di due argomenti termina il programma restituendo un messaggio di errore
	if (argc != 2) {
		puts("ERRORE: argomento non valido!");
		printf("USO: %s input_file\n", argv[0]);
		return 1;
	}

	//apre il file di lettura specificato dall'utente
	if (!(fin = fopen(argv[1], "r"))) {
		printf("ERRORE: il file di input \"%s\" non è stato trovato", argv[0]);
		return 1;
	}

	//conte il numero delle righe presenti nel file
	while (fgets(buf, sizeof(buf), fin) != NULL) {
		n_righe++;
	}

	//chiamata alla funzione per il conteggio del numero di gare
	//se non ci sono 20 piloti per gara significa che il file è corrotto e termina il programma
	if (f_numero_gare(n_righe) != 0) {
		return 1;
	}
	
	//chiamata alla funzione per stampare il pilota vincitore
	//in questa funzione è presente anche la chiamata alla funzione per stampare la squadra vincitrice
	f_pilota_vincitore(n_righe, fin);
	
	//chiude il file di lettura
	fclose(fin);	
	
	return 0;
}


int f_numero_gare(int n_righe)
{
	if (n_righe % N_PILOTI != 0) {
		puts("ERRORE: file corrotto");
		return 1;
	}
	else {
		printf("[NUMERO_GARE]\n%d\n", n_righe / N_PILOTI);
		return 0;
	}
}

void f_pilota_vincitore(int n_righe, FILE *fin) {
	Dati vect[N_PILOTI];
	Dati matrix[N_PILOTI][N_GARE];
	Dati classifica[N_PILOTI];
	char buf[300];
	int i;
	int j;
	int k;
	int punteggio[N_PILOTI] = {25, 18, 15, 12, 10, 8, 6, 4, 2, 1};
	char pilota[40];
	int k_primo_pilota = 0;
	int punteggio_primo_pilota = -1;
	char conf_pilota1[40];
	char conf_pilota2[40];
	char primo_classificato[40];
	int pari = 0; //condizione di default FALSA: non ci sono piu' vincitori

	//torna all'inizio del file di lettura
	fseek(fin, 0, SEEK_SET);

	if (n_righe == 20) {	//CASO PARTICOLARE: gara singola
		fgets(buf, sizeof(buf), fin);
		sscanf(buf, "%s", pilota);		

		strcpy(vect[0].pilota, pilota);
		vect[0].punteggio = punteggio[0];

		puts("\n[PILOTA_VINCITORE]");
		printf("%s %d\n", vect[0].pilota, vect[0].punteggio);

		for (i = 1; i < N_PILOTI; i++) {
			fgets(buf, sizeof(buf), fin);
			sscanf(buf, "%s", pilota);

			strcpy(vect[i].pilota, pilota);
			vect[i].punteggio = punteggio[i];
		}

		f_team_vincitore_gara_singola(vect, fin); //funzione dedicata in caso di una gara singola
	}

	else {	//CASO GENERALE
		//inizializza a zero tutti i campi "punteggio" della matrice
		for (j = 0; j < N_GARE; j++) {
			for (i = 0; i < N_PILOTI; i++) {
				matrix[i][j].punteggio = 0;
			}
		}	
	
		//copia nei campi "pilota" e "punteggio" della matrice (piloti x gare) i relativi dati prelevati dal
		//file di input
		for (j = 0; j < n_righe / N_PILOTI; j++) {
			for (i = 0; i < N_PILOTI; i++) {
				fgets(buf, sizeof(buf), fin);
				sscanf(buf, "%s", pilota);

				strcpy(matrix[i][j].pilota, pilota);
				matrix[i][j].punteggio = punteggio[i];
			}
		}

		//inizializza a zero il campo "punteggio" del vettore "classifica"
		for (k = 0; k < N_PILOTI; k++) {
			classifica[k].punteggio = 0;
		}

		//somma i punteggi dei piloti
		for (k = 0; k < N_PILOTI; k++) {	//k è l'indice dei piloti del vettore classifica
			for (j = 1; j < N_GARE; j++) {	//j è l'indice delle gare (colonna della matrice)
				for (i = 0; i < N_PILOTI; i++) { //i è l'indice dei piloti (riga della matrice)
					if (strcmp(matrix[i][j].pilota, matrix[k][0].pilota) == 0) {
						strcpy(classifica[k].pilota, matrix[i][j].pilota);
						classifica[k].punteggio = classifica[k].punteggio + matrix[i][j].punteggio;
					}	
				}
			}
			classifica[k].punteggio = classifica[k].punteggio + matrix[k][0].punteggio;
		}

		//salva in memoria l'indice k relativo al pilota vincitore
		for (k = 0; k < N_PILOTI; k++) {
			if (classifica[k].punteggio > punteggio_primo_pilota) {
				k_primo_pilota = k;
				punteggio_primo_pilota = classifica[k].punteggio;
			}
		}
	
		//salva in memoria il nome del pilota vincitore
		strcpy(primo_classificato, classifica[k_primo_pilota].pilota);

		//controlla se ci sono più vincitori
		//se ci sono più vincitori pari > 0
		for (k = 0; k < N_PILOTI; k++) {
			if (classifica[k].punteggio == punteggio_primo_pilota) {
				if (k_primo_pilota != k) {
					pari++;
				}
				else {
					pari--;
				}
			}
		}

		//se ci sono più vincitori viene stampato il nome del pilota che viene prima in ordine alfabetico
		if (pari > 0) {
			strcpy(conf_pilota1, classifica[0].pilota);
			for (k = 1; k < N_PILOTI; k++) {	//ciclo in caso di pareggio
				strcpy(conf_pilota2, classifica[k].pilota);
				i = 0;
				//il ciclo prosegue finché non viene trovata una lettera differente fra i due nomi
				while(conf_pilota2[i] == conf_pilota1[i]) {
						i++;
				}
				//viene salvato temporaneamente il pilota che viene prima in ordine alfabetico
				if (conf_pilota2[i] < conf_pilota1[i]) {
					strcpy(conf_pilota1, conf_pilota2);
				}
				//viene salvato definitivamente il pilota che viene prima in ordine alfabetico
				strcpy(primo_classificato, conf_pilota1);
			}
		}

		//stampa il nome del pilota vincitore e il relativo punteggio
		printf("\n[PILOTA_VINCITORE]\n%s %i\n", primo_classificato, punteggio_primo_pilota);

		f_team_vincitore(classifica, n_righe, fin);
	}
}


void f_team_vincitore(Dati classifica[], int n_righe, FILE *fin)
{
	int i;
	int j;
	char pilota[40];
	char team[40];
	char buf[300];
	char *scuderia[] = {"Ferrari", "Force_India", "Lotus", "Marussia", "McLaren", "Mercedes", "Red_Bull", "Sauber", "Toro_Rosso", "Williams"};
	Dati class_team[N_TEAM];
	int punteggio_prima_squadra = -1;
	int i_prima_squadra = 0;
	char prima_classificata[40];

	//torna all'inizio del file di lettura
	fseek(fin, 0, SEEK_SET);

	//inizializza a zero il campo "punteggio" del vettore "class_team"
	for (i = 0; i < N_TEAM; i++) {
		class_team[i].punteggio = 0;
	}

	//legge da file e registra i vari dati nel campo "team" del vettore classifica
	for (i = 0; i < N_PILOTI; i++) {
		fgets(buf, sizeof(buf), fin);
		sscanf(buf, "%s %s", pilota, team);
		strcpy(classifica[i].team, team);
	}

	//somma i punteggi dei piloti appartenenti alla stessa squadra
	for (i = 0; i < N_TEAM; i++) {	//scuderia
		for (j = 0; j < N_PILOTI; j++) {	//pilota
			if (strcmp(classifica[j].team, scuderia[i]) == 0) {
				strcpy(class_team[i].team, classifica[j].team);
				class_team[i].punteggio = class_team[i].punteggio + classifica[j].punteggio;
			}
		}
	}		

	//salva l'indice i relativo alla squadra vincitrice
	for (i = 0; i < N_TEAM; i++) {
			if (class_team[i].punteggio > punteggio_prima_squadra) {
				i_prima_squadra = i;
				punteggio_prima_squadra = class_team[i].punteggio;
			}
	}

	//memorizza la squadra vincitrice
	strcpy(prima_classificata, class_team[i_prima_squadra].team);

	//stampa il nome della squadra vincitrice e il relativo punteggio
	printf("\n[SQUADRA_VINCITRICE]\n%s %i\n", prima_classificata, punteggio_prima_squadra);
	
}


void f_team_vincitore_gara_singola(Dati vect[], FILE *fin)
{
	int i;
	int j;
	char pilota[40];
	char team[40];
	char buf[300];
	char *scuderia[] = {"Ferrari", "Force_India", "Lotus", "Marussia", "McLaren", "Mercedes", "Red_Bull", "Sauber", "Toro_Rosso", "Williams"};
	Dati class_team[10];
	int punteggio_prima_squadra = -1;
	int i_prima_squadra = 0;
	char prima_classificata[40];

	//torna all'inizio del file di lettura
	fseek(fin, 0, SEEK_SET);

	//inizializza a zero il campo "punteggio" del vettore "class_team"
	for (i = 0; i < N_TEAM; i++) {
		class_team[i].punteggio = 0;
	}

	//legge da file e registra i vari dati nel campo "team" del vettore classifica
	for (i = 0; i < N_PILOTI; i++) {
		fgets(buf, sizeof(buf), fin);
		sscanf(buf, "%s %s", pilota, team);
		strcpy(vect[i].team, team);
	}

	//somma i punteggi dei piloti appartenenti alla stessa squadra
	for (i = 0; i < N_TEAM; i++) {	//scuderia
		for (j = 0; j < N_PILOTI; j++) {	//pilota
			if (strcmp(vect[j].team, scuderia[i]) == 0) {
				strcpy(class_team[i].team, vect[j].team);
				class_team[i].punteggio = class_team[i].punteggio + vect[j].punteggio;
			}
		}
	}

	//salva l'indice i relativo alla squadra vincitrice
	for (i = 0; i < N_TEAM; i++) {
			if (class_team[i].punteggio > punteggio_prima_squadra) {
				i_prima_squadra = i;
				punteggio_prima_squadra = class_team[i].punteggio;
			}
		}

	//memorizza la squadra vincitrice
	strcpy(prima_classificata, class_team[i_prima_squadra].team);

	//stampa il nome della squadra vincitrice e il relativo punteggio
	printf("\n[SQUADRA_VINCITRICE]\n%s %i\n", prima_classificata, punteggio_prima_squadra);
	
}
