//stampa la somma dei numeri positivi inseriti (escluso l'ultimo negativo) dopo che si inserisce un numero negativo

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char s[80];
	int n;
	int max;
	int min;
	int n_elementi = 0;
	double media;
	int somma = 0;
	
	fgets(s, sizeof(s), stdin);
	n = atoi(s);
	max = n;
	min = n;
	n_elementi++;
	
	if (max < 0) {
			max = 0;
		}

	if (min < 0) {
			min = 0;
		}
		
	while (n > -1) {
		if (n > max) {
			max = n;
		}

		if (n < min) {
			min = n;
		}
		
		somma = somma + n;
		media = (double)somma / n_elementi;
		
		fgets(s, sizeof(s), stdin);
		n = atoi(s);
		n_elementi++;

	}
	
	printf("[SOMMA]\n%d\n", somma);
	printf("[MINIMO]\n%d\n", min);
	printf("[MASSIMO]\n%d\n", max);
	printf("[MEDIA]\n%lf\n", media);
	return 0;								
}
