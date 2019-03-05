#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//dichiarazioni tipo Punto e Rect per le seguenti strutture
typedef struct {
	double x;
	double y;
} Punto;

typedef struct {
	Punto A;
	Punto B;
} Rect;

//dichiarazioni di funzioni
void calcolo_distanza_origine(Punto vect[], int n);
void punti_nel_rettangolo(Punto vect[], int n);
void calcolo_area(double x_min, double x_max, double y_min, double y_max);
void maggiore_distanza(Punto vect[], int n);

int main()
{
	char s[80];	
	int n;
	int i;
	Punto vect[10];
	double x;
	double y;

	//permette l'inserimento di un valore n (punti) e controlla che sia compreso tra 1 e 10
	//se n > 10 -> n = 10
	puts("#Inserisci il numero di punti");
	fgets(s, sizeof(s), stdin);
	n = atoi(s);
	if (n < 1) {
		puts("#ERRORE: inserire un numero compreso tra 1 e 10");
		return 0;
	}
	if (n > 10) {
		n = 10;
	}

	//inserimento delle coordinate da tastiera e analisi dei valori inseriti con sscanf
	puts("#Inserisci le coordinate dei punti. Es: 1 2 per il punto (1, 2).");
	for (i = 0; i < n; i++) {
		fgets(s, sizeof(s), stdin);
		sscanf(s, "%lf %lf", &x, &y);
		vect[i].x = x;
		vect[i].y = y;
	}

	//stampa delle coordinate inserite
	puts("\n[PUNTI]");
	for (i = 0; i < n; i++) {
		printf("(%.3lf, %.3lf)\n", vect[i].x, vect[i].y);
	}

	//chiamate a funzioni
	calcolo_distanza_origine(vect, n);
	punti_nel_rettangolo(vect, n);
	
	if (n > 1) {	
		maggiore_distanza(vect, n);
	}
	
	return 0;	
}


void calcolo_distanza_origine(Punto vect[], int n)
{
	//funzione per il calcolo della distanza dei punti dall'origine
	double distanza_origine;
	int i;

	puts("\n[DISTANZE]");
	for (i = 0; i < n; i++) {
		distanza_origine = sqrt(pow(vect[i].x, 2) + pow(vect[i].y, 2));
		printf("%.3lf\n", distanza_origine);
	}
}


void punti_nel_rettangolo(Punto vect[], int n)
{
	//funzione per determinare i punti contenuti sui bordi o all'interno del rettangolo definito dall'utente
	char s[80];
	double x_cord;
	double y_cord;
	Rect Rettangolo;
	double x_max;
	double x_min;
	double y_max;
	double y_min;
	int i;

	//inserimento delle coordinate dei punti A e B per determinare il rettangolo
	puts("\n#Inserire le coordinate dei punti A e B seguendo lo schema usato in precedenza");
	fgets(s, sizeof(s), stdin);
	sscanf(s, "%lf %lf", &x_cord, &y_cord);
	Rettangolo.A.x = x_cord;
	Rettangolo.A.y = y_cord;
	fgets(s, sizeof(s), stdin);
	sscanf(s, "%lf %lf", &x_cord, &y_cord);
	Rettangolo.B.x = x_cord;
	Rettangolo.B.y = y_cord;

	//determina le coordinate degli estremi del rettangolo
	if (Rettangolo.B.x > Rettangolo.A.x) {
		x_max = Rettangolo.B.x;
		x_min = Rettangolo.A.x;
	}
	else {
		x_min = Rettangolo.B.x;
		x_max = Rettangolo.A.x;
	}
	if (Rettangolo.B.y > Rettangolo.A.y) {
		y_max = Rettangolo.B.y;
		y_min = Rettangolo.A.y;
	}
	else {
		y_min = Rettangolo.B.y;
		y_max = Rettangolo.A.y;
	}

	//stampa i punti interni al rettangolo
	puts("\n[INTERNI]");
	for (i = 0; i < n; i++) {
		if ((vect[i].x >= x_min && vect[i].x <= x_max) && (vect[i].y >= y_min && vect[i].y <= y_max)) {
			printf("(%.3lf, %.3lf)\n", vect[i].x, vect[i].y);
		}
	}

	//chiama funzione per il calcolo dell'area
	calcolo_area(x_min, x_max, y_min, y_max);
}


void calcolo_area(double x_min, double x_max, double y_min, double y_max)
{
	double area;	
	
	area = (x_max - x_min) * (y_max - y_min);
	printf("\n[AREA]\n%.3lf\n", area);
}


void maggiore_distanza(Punto vect[], int n)
{
	//funzione per determinare la coppia di punti che hanno la maggior distanza fra loro
	int i;
	int j;
	int i_max;
	int j_max;
	double distance;
	double max_distance = 0;

	for (i = 0; i < n; i++) {
		for (j = i + 1; j < n; j++) {
			distance = sqrt(pow((vect[i].x - vect[j].x), 2) + pow((vect[i].y - vect[j].y), 2));
			if (distance > max_distance) {
				max_distance = distance;
				i_max = i;
				j_max = j;
			}
		}
	}
	
	printf("\n[COPPIA]\n(%.3lf, %.3lf)\n(%.3lf, %.3lf)\n", vect[i_max].x, vect[i_max].y, vect[j_max].x, vect[j_max].y);
}
