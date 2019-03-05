//programma per il calcolo del discriminante di un equazione di secondo grado

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double discriminante (double a, double b, double c);

int main(int argc, char *argv[])
{
	char s[3];
	int guida;
	double a;
	double b;
	double c;

	if (argc != 4) {
		puts("ARGOMENTI NON VALIDI:\nPer una guida digitare \"1\"\nPer chiudere il programma digitare un qualsiasi altro carattere");
		
		fgets(s, sizeof(s), stdin);
		guida = atoi(s);

		if (guida == 1) {
			puts("Per inserire gli argomenti dell'equazione ax^2 + bx +c = 0 e calcolare il discriminante devi digitare da terminale:");
			puts("./discriminante a b c");
			puts("sostituendo a, b e c con dei numeri a piacere.");
		}
		
		return 1;
	}

	a = atof(argv[1]);
	b = atof(argv[2]);
	c = atof(argv[3]);

	//chiama la funzione discriminante e stampa il risultato
	printf("Il discriminante dell'equazione (%lf)x^2 + (%lf)x + (%lf) = 0 è %lf\n", a, b, c, discriminante(a, b, c));

	return 0;
	
}


double discriminante (double a, double b, double c)
{
	return (pow(b, 2) - 4 * a * c);
}
