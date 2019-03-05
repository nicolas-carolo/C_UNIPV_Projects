#include <stdio.h>
#include <stdlib.h>

void media_righe(int matrix[][4]);
void media_colonne(int matrix[][4]);
void media(int matrix[][4]);
void frequenza_valori(int matrix[][4]);
void ruota_matrix(int matrix[][4]);

int main()
{
	int matrix[4][4];
	char s[80];
	int k;
	int n;

	//cicli nidificati che permettono all'utente di inserire 16 valori compresi tra -5 e 5
	//i valori vengono ordinati in una matrice 4x4
	for (k = 0; k < 4; k++) {
		for (n = 0; n < 4; n++) {
			do {
   				fgets(s, sizeof(s), stdin);
				matrix[k][n] = atoi(s);
				if (matrix[k][n] < -5 || matrix[k][n] > 5) {
					puts("ERRORE! Inserire un valore compreso tra -5 e 5");
				}
			} while (matrix[k][n] < -5 || matrix[k][n] > 5);
   				
		}
	}

	puts("");

	//chiamate alle specifiche funzioni
	media_righe(matrix);
	media_colonne(matrix);
	media(matrix);
	frequenza_valori(matrix);
	ruota_matrix(matrix);

	return 0;
}


void media_righe(int matrix[][4])
{
	double somma = 0;
	double media = 0;
	int k;
	int n;

	puts("[MEDIA_RIGHE]");
	
	for (k = 0; k < 4; k++) {
		for (n = 0; n < 4; n++) {
			somma = somma + matrix[k][n];
		}
			media = somma / 4;
			printf("%lf\n", media);
			somma = 0;
			media = 0;
	}

	puts("");

}


void media_colonne(int matrix[][4])
{
	double somma = 0;
	double media = 0;
	int k;
	int n;

	puts("[MEDIA_COLONNE]");
	
	for (n = 0; n < 4; n++) {
		for (k = 0; k < 4; k++) {
			somma = somma + matrix[k][n];
		}
			media = somma / 4;
			printf("%lf\n", media);
			somma = 0;
			media = 0;
	}

	puts("");

}


void media(int matrix[][4])
{
	double somma = 0;
	double media = 0;
	int k;
	int n;

	puts("[MEDIA]");
	
	for (n = 0; n < 4; n++) {
		for (k = 0; k < 4; k++) {
			somma = somma + matrix[k][n];
		}
	}

	media = somma / 16;
	printf("%lf\n", media);

	puts("");

}


void frequenza_valori(int matrix[][4])
{
	int frequenza = 0;
	int valore;
	int k;
	int n;

	puts("[FREQUENZE]");
	for (valore = -5; valore <= 5; valore++) {
		for (n = 0; n < 4; n++) {
			for (k = 0; k < 4; k++) {
				if (matrix[k][n] == valore) {
					frequenza++;
				}
			}
		}
		printf("%d\n", frequenza);
		frequenza = 0;
	}
	
	puts("");
}


void ruota_matrix(int matrix[][4])
{
	int k;
	int n;
	int matrix_ruotata[4][4];

	puts("[RUOTA]");
	
	for (n = 0; n < 4; n++) {
		for (k = 0; k < 4; k++) {
			matrix_ruotata[n] [3-k] = matrix[k][n];	
		}
	}

	printf("%d  %d  %d  %d\n", matrix_ruotata[0][0], matrix_ruotata[0][1], matrix_ruotata[0][2], matrix_ruotata[0][3]);
	printf("%d  %d  %d  %d\n", matrix_ruotata[1][0], matrix_ruotata[1][1], matrix_ruotata[1][2], matrix_ruotata[1][3]);
	printf("%d  %d  %d  %d\n", matrix_ruotata[2][0], matrix_ruotata[2][1], matrix_ruotata[2][2], matrix_ruotata[2][3]);
	printf("%d  %d  %d  %d\n", matrix_ruotata[3][0], matrix_ruotata[3][1], matrix_ruotata[3][2], matrix_ruotata[3][3]);

	puts("");

}
