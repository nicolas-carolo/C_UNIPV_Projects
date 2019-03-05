//programma per la valutazione di un polinomio di grado n in un punto

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double valuta(double coefficiente[], int x, int n);

int main(int argc, char *argv[])
{
	int i;
	int n = argc - 3;
	double coefficiente[argc - 2];
	double x = atof(argv[argc - 1]);

	if(argc < 4) {
		puts("ERRORE: argomenti insufficienti!");
		puts("Inserire prima n coefficienti e poi il valore di x per il quale eseguire la valutazione");
		puts("ESEMPIO: ./poly 2 0 -4 3.14");
		puts("per valutare il polinomio 2x^3 - 4x per x = 3.14");
		return 1;
	}
	
	//converte i coefficienti a valori double e li memorizza nel vettore coefficiente[] in ordine decresente
	for (i = 1; i <= n + 1; i++) {
		coefficiente[i - 1] = atof(argv[i]);
	}
	
	printf("Il polinomio nel punto x = %lf ha un valore pari a %lf\n", x, valuta(coefficiente, x, n));	

	return 0;
}


double valuta(double coefficiente[], int x, int n)
{
	double y = 0;
	int i;
	int grado = n;

	for (i = 0; i <= n; i++) {	
		y = y + (pow(x, grado) * coefficiente[i]);
		grado--;
	}

	return y;
}
