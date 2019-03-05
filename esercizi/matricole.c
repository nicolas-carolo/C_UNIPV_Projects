#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int studente;
	int esame;
	int voto;
} Matricola;

void esami_superati_per_studente(Matricola vect[]);
void voti_registrati(Matricola vect[]);

int main()
{
	Matricola vect[800];	//8 esami x 100 studenti
	char s[80];
	int n_input;
	int studente;
	int esame;
	int voto;
	int i;

	//inizializza a zero i valori contenuti nel vettore vect
	for (i = 0; i < 800; i++) {
		vect[i].studente = 0;
		vect[i].esame = 0;
		vect[i].voto = 0;
	}
	
	//chiede all'utente di registrare i dati nel modo indicato
	puts("Inserire i dati nel seguente modo: n° studente (1-100) n° esame (1-8) voto esame (18-30)");
	puts("Esempio: 56 5 24");
	puts("Per terminare il programma premere invio senza inserire alcun dato");

	//il ciclo continua fino a che l'utente non preme invio senza inserire alcun dato
	while (1) {
		fgets(s, sizeof(s), stdin);
		n_input = sscanf(s, "%i %i %i", &studente, &esame, &voto);

		//condizione di fine del ciclo
		if (n_input == -1) {
			break;
		}

		//se l'input non è composto da tre elementi termina il programma
		if (n_input != 3) {
			puts("ERRORE: input non valido!");			
			return 1;
		}

		//si assicura che i valori inseriti rispettano determinati parametri
		//in caso contrario termina il programma
		if (studente < 1 || studente > 100) {
			puts("ERRORE: il numero dello studente deve essere compreso tra 1 e 100");
			return 1;
		}
		if (esame < 1 || esame > 8) {
			puts("ERRORE: il numero dell'esame deve essere compreso tra 1 e 8");
			return 1;
		}
		if (voto < 18 || voto > 30) {
			puts("ERRORE: il voto deve essere compreso tra 18 e 30");
			return 1;
		}

		//registra i dati acquisiti all'interno di un vettore in modo tale che i voti degli studenti
		//siano registrati in modo contiguo per ordine crescente di numero di studente e di numero di esame
		vect[((studente - 1) * 8) + (esame - 1)].studente = studente;
		vect[((studente - 1) * 8) + (esame - 1)].esame = esame;
		vect[((studente - 1) * 8) + (esame - 1)].voto = voto;
	}

	//chiamate alle funzioni separate da andate-a-capo
	puts("");
	esami_superati_per_studente(vect);
	puts("");
	voti_registrati(vect);
	puts("");
	
	return 0;
}


void esami_superati_per_studente(Matricola vect[])
{
	//funzione che calcola gli esami superati da ciascun studente e la media di ogni studente
	int i;
	int j;
	int esami_superati = 0;
	int somma_voti = 0;
	double media_esami;

	for (i = 1; i <= 100; i++) {	//incrementa l'indice dello studente
		for (j = (i - 1) * 8; j < (i - 1) * 8 + 8; j++) {	//incrementa l'indice dell'esame
			if (vect[j].studente != 0) {
				esami_superati++;	//conteggia gli esami superati da ciascuno studente
				somma_voti = somma_voti + vect[j].voto;	//fa la somma dei voti di ogni studente	
			}
		}
		//viene effettuata la stampa dei risultati di uno studente solo se quest'ultimo ha superato almeno un esame
		if (esami_superati != 0) {
			media_esami = (double)somma_voti/esami_superati;
			printf("Lo studente numero %i ha superato %i esami con una media di %.2lf/30\n", i, esami_superati, media_esami); 
			esami_superati = 0;
			somma_voti = 0;
		}
	}
}


void voti_registrati(Matricola vect[])
{
	//funzione che calcola il numero di studenti che passano un dato esame e la media per esame
	int i;
	int j;
	int voti_registrati = 0;
	int somma_voti = 0;
	double media_esami;

	for (i = 1; i <= 8; i++) {	//incrementa l'indice dell'esame
		j = i - 1;
		while (j < 800) {	//incrementa l'indice dello studente
			if (vect[j].esame != 0) {
				voti_registrati++;
				somma_voti = somma_voti + vect[j].voto;		
			}
			j = j + 8;	//i voti di un esame sono registrati a distanza di 8 elementi
		}
		if (voti_registrati != 0) {	//caso in cui almeno uno studente ha superato un esame
			media_esami = (double)somma_voti/voti_registrati;
			printf("L'esame numero %i è stato superato da %i studenti con una media di %.2lf/30\n", i, voti_registrati, media_esami); 
		}		
		else {				//caso in cui nessuno studente ha superato un dato esame
			printf("L'esame numero %i non è stato superato da nessuno studente\n", i);
		}
		voti_registrati = 0;
		somma_voti = 0;
	}	

}

