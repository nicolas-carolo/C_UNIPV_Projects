//valuta il polinomio ax^2 + bx + c nel punto x per che varia in [0, 3] con incrementi di 0.1

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double valuta(double a, double b, double c, double x);

int main(int argc, char *argv[])
{
	char s[3];
	int guida;
	double a;
	double b;
	double c;
	double x = 0;

	if (argc != 4) {
		puts("ARGOMENTI NON VALIDI:\nPer una guida digitare \"1\"\nPer chiudere il programma digitare un qualsiasi altro carattere");
		
		fgets(s, sizeof(s), stdin);
		guida = atoi(s);

		if (guida == 1) {
			puts("Per inserire gli argomenti del polinomio ax^2 + bx +c = 0 digitare da terminale:");
			puts("./valuta polinomio a b c");
			puts("sostituendo a, b e c con i coefficienti del polinomio.");
		}
		
		return 1;
	}

	a = atof(argv[1]);
	b = atof(argv[2]);
	c = atof(argv[3]);

	//chiama la funzione valuta e itera il processo
	while (x < 3.1) {
		printf("p(%.1lf) = %.2lf\n", x, valuta(a, b, c, x));
		x = x + 0.1;
	}

	return 0;
}

double valuta(double a, double b, double c, double x)
{
	return(a * pow(x, 2) + b * x + c);
}
