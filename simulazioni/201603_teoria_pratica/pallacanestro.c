#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char squadra[100];
	int punti;
	int persa_vinta; //0=PERSA | 1=VINTA
	int giocate;
	int vinte;
} Dati;

void f_punteggio_migliore(Dati *vect_team, int n_semiline);
void f_n_vittorie_casa_fuori(Dati *vect_team, int n_semiline);
void f_media_punti(Dati *vect_team, int n_semiline);
int f_stampa_squadre(Dati *vect_team, Dati *list_team, int n_semiline);
void f_partite_giocate(Dati *vect_team, Dati *list_team, int n_semiline, int n_team);
void f_partite_vinte(Dati *vect_team, Dati *list_team, int n_semiline, int n_team);
void swap(Dati *a, Dati *b);
void f_stampa_classifica(Dati *list_team, int n_team);

int main(int argc, char *argv[])
{
	FILE *fin;
	char line[512];
	int d = 10;
	int n_line = 0;
	int n_semiline = 0;
	int n_team;
	Dati *vect_team = malloc(d * sizeof(Dati));
	Dati *list_team = malloc(d * sizeof(Dati));
	
	if (argc != 2) {
		printf("#USO: %s input_file\n", argv[0]);
		return 1;
	}
	
	if (!(fin = fopen(argv[1], "r"))) {
		return -1;	
	}

	
	while (fgets(line, sizeof(line), fin)) {
		sscanf(line, "%s vs %s %d - %d", vect_team[n_semiline].squadra, vect_team[n_semiline + 1].squadra, &vect_team[n_semiline].punti, &vect_team[n_semiline + 1].punti);
		
		//assegna la vittora o la sconfitta ad una squadra
		if (vect_team[n_semiline].punti > vect_team[n_semiline + 1].punti) {
			vect_team[n_semiline].persa_vinta = 1;
			vect_team[n_semiline + 1].persa_vinta = 0;		
		}
		else {
			vect_team[n_semiline].persa_vinta = 0;
			vect_team[n_semiline + 1].persa_vinta = 1;	
		}

		n_line++;
		n_semiline = n_semiline + 2;
		
		//se si necessita di piu' spazio la funzione realloc incrementa lo spazio
		if (n_semiline >= d) {
			d = d + 2;
			vect_team = realloc(vect_team, d * sizeof(Dati));
			if (vect_team == NULL) {	//se non e' possibile riallocare la memoria il programma termina
				puts("ERRORE: impossibile allocare altro spazio dinamicamente!");
				return 1;
			}
		}
	}

	f_punteggio_migliore(vect_team, n_semiline);
	f_n_vittorie_casa_fuori(vect_team, n_semiline);
	f_media_punti(vect_team, n_semiline);
	n_team = f_stampa_squadre(vect_team, list_team, n_semiline);
	f_partite_giocate(vect_team, list_team, n_semiline, n_team);
	f_partite_vinte(vect_team, list_team, n_semiline, n_team);
	f_stampa_classifica(list_team, n_team);

	free(vect_team);
	free(list_team);
	fclose(fin);
	return 0;
}

void f_punteggio_migliore(Dati *vect_team, int n_semiline)
{
	//funzione che stampa a video i nomi delle squadre che hanno totalizzato il maggiorn numero
	//di punti in una singola partita
	int punteggio_migliore = 0;
	int i;
	int d = 1;
	Dati *team_best_score = malloc(d * sizeof(Dati));

	for (i = 0; i < n_semiline; i++) {
		if (vect_team[i].punti == punteggio_migliore) {
			d = d + 1;
			team_best_score = realloc(team_best_score, d * sizeof(Dati));
			if (team_best_score == NULL) {
				puts("ERRORE: impossibile allocare altro spazio dinamicamente!");
			}
			
			strcpy(team_best_score[d-1].squadra, vect_team[i].squadra);
			team_best_score[d-1].punti = vect_team[i].punti;
		}
		if (vect_team[i].punti > punteggio_migliore) {
			punteggio_migliore = vect_team[i].punti;
			d = 1;
			team_best_score = realloc(team_best_score, d * sizeof(Dati));
			if (team_best_score == NULL) {
				puts("ERRORE: impossibile allocare altro spazio dinamicamente!");
			}

			strcpy(team_best_score[0].squadra, vect_team[i].squadra);
			team_best_score[0].punti = vect_team[i].punti;	
		}
	}

	puts("\n[PUNTEGGIO-MIGLIORE]");

	for (i = 0; i < d; i++) {
		printf("%s\n", team_best_score[i].squadra);
	}
	
	free(team_best_score);
}


void f_n_vittorie_casa_fuori(Dati *vect_team, int n_semiline)
{
	//funzione che stampa a video il totale delle vittore avvenute in casa e in trasferta
	int i;
	int vittorie_casa = 0;
	int vittorie_trasferta = 0;

	for (i = 0; i < n_semiline; i = i + 2) {
		vittorie_casa = vittorie_casa + vect_team[i].persa_vinta;	
	}

	vittorie_trasferta = (n_semiline / 2) - vittorie_casa;

	puts("\n[VITTORIE]");
	printf("%d\n", vittorie_casa);
	printf("%d\n", vittorie_trasferta);
}


void f_media_punti(Dati *vect_team, int n_semiline)
{
	//funzione che stampa a video la media delle somme dei punti delle squadre
	//fatti nelle singole partite
	int i;
	int totale_punti = 0;
	double media;

	for (i = 0; i < n_semiline; i++) {
		totale_punti = totale_punti + vect_team[i].punti;
	}

	media = (double)totale_punti / (n_semiline / 2);
	printf("\n[MEDIA]\n%lf\n", media); 
}


int f_stampa_squadre(Dati *vect_team, Dati *list_team, int n_semiline)
{
	//funzione che stampa a video l'elenco delle squadre nell'ordine in cui compaiono nel file di input
	int i = 0;
	int j;
	int div = 0;
	int n_team = 0;
	
	puts("[SQUADRE]");
	printf("%s\n",vect_team[0].squadra);
	strcpy(list_team[n_team].squadra, vect_team[i].squadra);
	for (i = 1; i < n_semiline; i++) {
		for (j = 0; j < i; j++) {
			if (strcmp(vect_team[i].squadra, vect_team[j].squadra) != 0) {
				div++;
			}
		}
		if (div == j){
			printf("%s\n",vect_team[i].squadra);			
			n_team++;
			strcpy(list_team[n_team].squadra, vect_team[i].squadra);
					
		}
		div = 0;
	}
	
	n_team++;
	
	return n_team;
}

void f_partite_giocate(Dati *vect_team, Dati *list_team, int n_semiline, int n_team)
{
	//funzione che calcola il numero delle partite giocate da ogni squadra salvando
	//il totale nell'apposito campo
	int i;
	int j;
	int count_partite = 0;

	for (i = 0; i < n_team; i++) {
		for (j = 0; j < n_semiline; j++) {
			if (strcmp(list_team[i].squadra, vect_team[j].squadra) == 0) {
				count_partite++;
			} 
		}

		list_team[i].giocate = count_partite;
		count_partite = 0;
	}
}


void f_partite_vinte(Dati *vect_team, Dati *list_team, int n_semiline, int n_team)
{
	//funzione che calcola il numero delle vittorie di ogni squadra salvando
	//il totale nell'apposito campo
	int i;
	int j;
	int count_vinte = 0;

	for (i = 0; i < n_team; i++) {
		for (j = 0; j < n_semiline; j++) {
			if ((strcmp(list_team[i].squadra, vect_team[j].squadra) == 0) && (vect_team[j].persa_vinta == 1)) {
				count_vinte++;
			} 
		}

		list_team[i].vinte = count_vinte;
		count_vinte = 0;
	}	
}


void f_stampa_classifica(Dati *list_team, int n_team)
{
	//funzione che stampa la classifica in ordine alfabetico
	int i;
	int j;

	for (i = 0; i < n_team; i++) {
		for (j = 0; j < n_team; j++) {
			if (strcmp(list_team[i].squadra, list_team[j].squadra) < 0) {
				swap(&list_team[i], &list_team[j]);
			}
		}
	}

	puts("\n[PARTITE]");
	for (i = 0; i < n_team; i++) {
		printf("%s %d %d\n",list_team[i].squadra, list_team[i].giocate, list_team[i].vinte);
	}		
}


void swap(Dati *a, Dati *b)
{
	Dati tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

