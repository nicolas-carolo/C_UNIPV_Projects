//Date le misure dei lati di un rettangolo fornite da linea di comando, calcola e stampa il perimetro, l'area e la diagonale del rettangolo

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double perimetro(double base, double altezza);
double area(double base, double altezza);
double diagonale(double base, double altezza);

int main(int argc, char *argv[])
{
	double a;
	double b;

	if (argc != 3)	{
		puts("ERRORE: dati non validi! Inserire le misure dei due lati del rettangolo.");
		return 1;
	}
	
	a = atof(argv[1]);
	b = atof(argv[2]);

	//stampa la misura del perimetro chiamando la funzione perimetro
	printf("\n[PERIMETRO]\n%lf\n", perimetro(a, b));

	//stampa la misura dell'area chiamando la funzione area
	printf("\n[AREA]\n%lf\n", area(a, b));

	//stampa la misura della diagonale chiamando la funzione diagoanle
	printf("\n[DIAGONALE]\n%lf\n", diagonale(a, b));
	
	return 0;

}


double perimetro(double base, double altezza)
{
	return(base + altezza) * 2;
}


double area(double base, double altezza)
{
	return(base * altezza);
}


double diagonale(double base, double altezza)
{
	return (sqrt(pow(base, 2) + pow(altezza, 2)));
}
