//dati 3 numeri inseriti da riga di comando verifica se possono essere le misure dei tre lati di un rettangolo

#include <stdio.h>
#include <stdlib.h>

double maggiore(double n1, double n2, double n3);
double minore(double n1, double n2, double n3);
double intermedio(double n1, double n2, double n3, double n_max, double n_min);
void verifica(double n_min, double n_int, double n_max);

int main(int argc, char *argv[])
{
	double a;
	double b;
	double c;
	double lato_maggiore;
	double lato_minore;
	double lato_intermedio;

	if (argc != 4) { //permette l'inserimento di 3 parametri
		puts("ERRORE: inserire 3 misure!");
		return 1;
	}

	a = atof(argv[1]);
	b = atof(argv[2]);
	c = atof(argv[3]);

	//registra il lato maggiore
	lato_maggiore = maggiore(a, b, c);

	//registra il lato minore
	lato_minore = minore(a, b, c);

	//registra il lato intermedio
	lato_intermedio = intermedio(a, b, c, lato_maggiore, lato_minore);

	//verifica se i valori inseriti sono validi come misure dei lati di un triangolo
	verifica(lato_minore, lato_intermedio, lato_maggiore);

	return 0;

}


double maggiore(double n1, double n2, double n3)
{
	double max;

	max = n1;

	if (n2 > max) {
		max = n2;
	}

	if (n3 > max) {
		max = n3;
	}

	return max;

}


double minore(double n1, double n2, double n3)
{
	double min;

	min = n1;

	if (n2 < min) {
		min = n2;
	}

	if (n3 < min) {
		min = n3;
	}

	return min;

}


double intermedio(double n1, double n2, double n3, double n_max, double n_min)
{
	if ((n2 == n_min && n3 == n_max) || (n3 == n_min && n2 == n_max)) {
		return n1;
	}
	
	if ((n1 == n_min && n3 == n_max) || (n3 == n_min && n1 == n_max)) {
		return n2;
	}

	return n3;
}


void verifica(double n_min, double n_int, double n_max)
{
	if (n_min + n_int > n_max) {
		puts("I valori inseriti possono essere le misure dei lati di un triangolo");
	}
	else {
		puts("I valori inseriti NON possono essere le misure dei lati di un triangolo");
	}
}
