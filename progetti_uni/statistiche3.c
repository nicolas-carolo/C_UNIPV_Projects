#include <stdio.h>
#include <stdlib.h>

int main()
{
	char s[80];
	int n;
	int max;
	int min;
	int n_elementi = 0;
	int n_pari = 0;
	int primo_numero;
	int n_magg_primo = 0;
	double media = 0;
	int somma = 0;
	
	fgets(s, sizeof(s), stdin);
	n = atoi(s);
	max = n;
	min = n;
	primo_numero = n;
	n_elementi++;
	
	//in caso di mancanza di valori positivi max = min = 0
	if (max < 0) {
			max = 0;
		}

	if (min < 0) {
			min = 0;
		}
		
	while (n > -1) {
		//memorizza rispettivamente il maggiore e il minore
		if (n > max) {
			max = n;
		}

		if (n < min) {
			min = n;
		}

		//controlla se n e' pari
		if (n % 2 == 0) {
			n_pari++;
		}

		//controlla se e' maggiore del primo numero
		if (n > primo_numero) {
			n_magg_primo++;
		}
		
		somma = somma + n;
		media = (double)somma / n_elementi;
		
		//inserimento secondo numero		
		fgets(s, sizeof(s), stdin);
		n = atoi(s);
		n_elementi++;

	}
	
	//stampa i risultati
	printf("[SOMMA]\n%d\n", somma);
	printf("[MINIMO]\n%d\n", min);
	printf("[MASSIMO]\n%d\n", max);
	printf("[MEDIA]\n%lf\n", media);
	printf("[PARI]\n%d\n", n_pari);
	printf("[MAGGIORI_DEL_PRIMO]\n%d\n", n_magg_primo);
	return 0;								
}
