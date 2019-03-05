//per scartare una variabile int prelevata con sscanf devo utilizzare %*d

#include <stdio.h>
#include <stdlib.h>

#define MAX_TARIFFA 7
#define N_MESI 6
#define N_GIORNI 31

typedef struct {
	int giorno;
	int mese;
	int anno;
} Data;

typedef struct {
	Data day;
	int permanenza;
	double prezzo;
} Ingresso;

typedef struct {
	int minuti;
	double prezzo;
} Tariffa;

int calcola_permanenza(int ora_in, int min_in, int ora_out, int min_out);
void calcolo_incasso(Ingresso *a, int n_righe);
void trova_mese_max_ingressi(Ingresso *a, int n_righe);
void trova_giorno_max_ingressi(Ingresso *a, int n_righe);

int main(int argc, char *argv[])
{
	int d = 10;
	int n_righe = 0;
	int i = 0;
	Ingresso *a = malloc(d * sizeof(Ingresso));	//allocazione dinamica di un vettore per salvare un numero non noto di elementi
	char buf[1024];
	FILE *fin;
	Tariffa prezzi[4] = {{20, 3.5}, {30, 4}, {45, 4.5}, {60, 5.5}};
	int ora_in;
	int min_in;
	int ora_out;
	int min_out;

	if (argc != 2) {
		printf("USO: %s [input_file]", argv[0]);
	}

	//apertura del file con relativi controlli di corretto funzionamento
	if (!(fin = fopen(argv[1], "r"))) {
		printf("ERRORE: il file di input \"%s\" non è stato trovato\n", argv[1]);
		return 1;
	}

	//il ciclo di lettura prosegue fino alla restituzione di NULL
	while (fgets(buf, sizeof(buf), fin)) {
		sscanf(buf, "%d/%d/%d %*d %d:%d %d:%d", &a[n_righe].day.giorno, &a[n_righe].day.mese, &a[n_righe].day.anno, &ora_in, &min_in, &ora_out, &min_out);
		//chiama la funzione per il calcolo della permanenza di ogni utente nel parco e salva il dato restituito
		//nel campo dedicato di ogni elemento del vettore
		a[n_righe].permanenza = calcola_permanenza(ora_in, min_in, ora_out, min_out);
		
		//associa il prezzo in base alla permanenza di ogni utente e salva i dati per ogni elemento nel campo dedicato
		for (i = 0;i < 5; i++) {
			if (a[n_righe].permanenza > 60) {
				a[n_righe].prezzo = MAX_TARIFFA;
				break;
			}
			if (a[n_righe].permanenza <= prezzi[i].minuti) {
				a[n_righe].prezzo = prezzi[i].prezzo;
				break;
			}	
		}	
	
		n_righe++;	//conta il numero di righe del file di input

		//se si necessita di piu' spazio la funzione realloc incrementa lo spazio
		if (n_righe >= d) {
			d = d + 2;
			a = realloc(a, d * sizeof(Ingresso));
			if (a == NULL) {	//se non e' possibile riallocare la memoria il programma termina
				puts("ERRORE: impossibile allocare altro spazio dinamicamente!");
				return 1;
			}
		}	
	}
	
	//stampa il numero di ingressi, ovvero il numero di righe
	printf("\n[INGRESSI]\n%d\n", n_righe);

	//chiamate a funzioni varie
	calcolo_incasso(a, n_righe);
	trova_mese_max_ingressi(a, n_righe);
	trova_giorno_max_ingressi(a, n_righe);

	//chiude il file
	fclose(fin);
	
	//libera la memoria allocata dinamicamente
	free(a);

	return 0;
}


int calcola_permanenza(int ora_in, int min_in, int ora_out, int min_out)
{
	//calcola la permanenza (espressa in minuti) di un utente
	int min_of_day_in;	//minuto della giornata di ingresso
	int min_of_day_out;	//minuto della giornata di uscita

	min_of_day_in = (ora_in * 60) + min_in;
	min_of_day_out = (ora_out * 60) + min_out;

	return (min_of_day_out - min_of_day_in);
}


void calcolo_incasso(Ingresso *a, int n_righe)
{
	//funzione per il calcolo degli incassi mensili e dell'incasso totale
	int i;
	int i_mese;
	double incasso_mese = 0;
	double incasso_totale = 0;
	char *nomi_mesi[] = {"Aprile", "Maggio", "Giugno", "Luglio", "Agosto", "Settembre"};

	puts("\n[INCASSO_MENSILE]");
	for (i_mese = 4; i_mese < 10; i_mese++) {
		for (i = 0; i < n_righe; i++) {
			if (a[i].day.mese == i_mese) {
				incasso_mese = incasso_mese + a[i].prezzo;
			}
		}
		incasso_totale = incasso_totale + incasso_mese;
		printf("%s %lf\n", nomi_mesi[i_mese - 4], incasso_mese);
		incasso_mese = 0;
	}

	printf("\n[INCASSO_TOTALE]\n%lf\n", incasso_totale);
}


void trova_mese_max_ingressi(Ingresso *a, int n_righe)
{
	//funzione per il calcolo del mese con piu' ingressi
	int ingressi[N_MESI] = {0};
	int i;
	int i_mese;
	int i_max = 0;
	int max_ingressi = -1;
	char *nomi_mesi[] = {"Aprile", "Maggio", "Giugno", "Luglio", "Agosto", "Settembre"};

	//salva nel vettore "ingressi" il numero di ingressi per ogni mese
	for (i_mese = 4; i_mese < 10; i_mese++) { //4->aprile 10->ottobre
		for (i = 0; i < n_righe; i++) {
			if (a[i].day.mese == i_mese) {
				ingressi[i_mese - 4]++;
			}
		} 		
	}

	//trova il mese con il maggior numero di ingressi e lo stampa
	for (i = 0; i < N_MESI; i++) {
		if (ingressi[i] > max_ingressi) {
			max_ingressi = ingressi[i];
			i_max = i;
		}
	}
	printf("\n[MESE_MAX_INGRESSI]\n%s\n", nomi_mesi[i_max]);
}


void trova_giorno_max_ingressi(Ingresso *a, int n_righe)
{
	//funzione per il calcolo del giorno con piu' ingressi
	int i;	//giorno
	int j;	//mese
	int k;
	int i_max;
	int j_max;
	int frequenza_max = -1;
	int frequenza[N_GIORNI][N_MESI] = {0};

	//riordina in una matrice giorni x mesi le frequenze
	for (j = 0; j < N_MESI; j++) {
		for (i = 0; i < N_GIORNI; i++) {
			for (k = 0; k < n_righe; k++) {
				if ((a[k].day.giorno == i + 1) && (a[k].day.mese == j + 4)) {
					frequenza[i][j]++;
				}
			}
		}
	}

	//cerca il giorno con il maggior numero di ingressi
	for (j = 0; j < N_MESI; j++) {
		for (i = 0; i < N_GIORNI; i++) {
			if (frequenza[i][j] > frequenza_max) {
				frequenza_max = frequenza[i][j];
				i_max = i;
				j_max = j;
			}
		}
	}
	
	//stampa il giorno con il maggior numero di ingressi
	printf("\n[GIORNO_MAX_INGRESSI]\n%d/%d/%d\n\n", i_max + 1, j_max + 4, a[i_max].day.anno);
}
