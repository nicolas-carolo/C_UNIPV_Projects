#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXDEGREE 10
#define EPSILON  1e-7

/*
 * Stampa i coefficienti del polinomio in ordine decrescente di grado
 *
 */
void stampaCoefficienti(double coefficienti[], int grado) {
	int i;
	/*
	 * grado e` il grado del polinomio
	 * il vettore coefficienti ha grado + 1 elementi da stampare
	 * percio` il ciclo parte da grado e arriva a 0 (compreso)
	 */
	for (i = grado; i >= 0; i--) {
		printf("%.6lf\n", coefficienti[i]);
	}
}

/*
 * Valuta il polinomio fornito dal vettore coefficienti nel punto x
 */
double valuta(double coefficienti[], int grado, double x) {
	int i;
	double y = coefficienti[0];
	double potenza = x;
	/*
	 * dato che y e` inizializzata a coefficienti[0] il ciclo parte da 1
	 * come prima ho da elaborare grado + 1 elementi
	 */
	for (i = 1; i < grado + 1; i++) {
		/* 
		 * si puo` anche fare y += coefficienti[i] * pow(x, i)
		 * ma e` meno efficiente
		 */
		y += coefficienti[i] * potenza;
		potenza *= x;
	}
	return y;
}

/*
 * Calcola la derivata del polinomio fornito
 * In questo caso il risultato della funzione e` messo nel vettore ris.
 * Infatti i vettori sono passati alla funzione per riferimento e quindi se il
 * loro contenuto e` modificato dalla funzione, questa modifica e` visibile al
 * chiamante.
 * Le variabili scalari invece sono passate per valore: la funzione riceve una
 * copia e quindi qualunque modifica venga fatta, questa non viene vista dal
 * chiamante
 */
void derivata(double coefficienti[], int grado, double ris[]) {
	int i;
	for (i = 0; i < grado; i++) {
		ris[i] = (i + 1) * coefficienti[i + 1];
	}
	ris[grado] = 0;
}

/*
 * Calcola l'integrale del polinomio fornito
 * Anche qui il risultato e` nel vettore ris.
 */
void integrale(double coefficienti[], int grado, double ris[]) {
	int i;
	for (i = grado; i >= 0; i--) {
		ris[i + 1] = coefficienti[i] / (i + 1);
	}
	ris[0] = 0;
}

/*
 * Calcola la soluzione dell'equazione polinomio = 0
 * In questa funzione riutilizzo le funzioni valuta e derivata
 */
double soluzione(double coefficienti[], int grado) {
	double xn = 1;
	double y = valuta(coefficienti, grado, xn);
	double der[MAXDEGREE];
	derivata(coefficienti, grado, der);
	/*
	 * fabs calcola il valore assoluto di una variabile double
	 * la si trova in math.h
	 * Attenzione: fabs si usa per i float e i double
	 * abs invece si usa solo per gli int
	 */
	while (fabs(y) >= EPSILON) {
		double yd = valuta(der, grado - 1, xn);
		xn = xn - y/yd;
		y = valuta(coefficienti, grado, xn);
	}
	return xn;
}


int main() {
	/* NOTA: pvcheck ignora le righe di output che iniziano con # */
	/*
	 * il + 1 e` dovuto al fatto che un polinomio di grado n a n + 1
	 * coefficienti, quindi un polinomio di grado MAXDEGREE ha MAXDEGREE + 1
	 * coefficienti.
	 * derivata e` lungo MAXDEGREE perche` la derivata di un polinomio di grado n
	 * e` un polinomio di grado n-1
	 * integrale e` lungo MAXDEGREE + 2 perche` l'integrale di un polinomio di grado n
	 * e` un polinomio di grado n + 1
	 */
	double polinomio[MAXDEGREE + 1], der[MAXDEGREE], integ[MAXDEGREE + 2];
	int i, n;
	char linea[1024];
	double x, y;
	/* Input dei dati */
	printf("# Inserire grado del polinomio (max: %d): ", MAXDEGREE);
	fgets(linea, sizeof(linea), stdin);
	n = atoi(linea);
	if (n < 0 || n > MAXDEGREE) {
		printf("\n[ERRORE]\n");
		printf("Grado non accettabile\n");
		/*
		 * la cosa piu` giusta sarebbe fare return 1
		 * ma pvcheck lo considera errore
		 */
		return 0;
	}
	for (i = 0; i < n + 1; i++) {
		printf("# Inserire il coefficiente di grado %d: ", i);
		fgets(linea, sizeof(linea), stdin);
		polinomio[i] = atof(linea);
	}
	/* Stampa dei coefficienti in ordine decrescente di grado */
	printf("\n[STAMPA]\n");
	stampaCoefficienti(polinomio, n);
	/* Valutazione del polinomio in x */
	printf("# Inserire il valore di x: ");
	fgets(linea, sizeof(linea), stdin);
	x = atof(linea);
	y = valuta(polinomio, n, x);
	printf("\n[VALUTA]\n");
	printf("%.6lf\n", y);
	/* Calcolo della derivata */
	/*
	 * der e` dichiarato nella funzione main ma verra` modificato dalla
	 * funzione derivata che vi memorizzera` il risultato dell'elaborazione
	 */
	derivata(polinomio, n, der);
	printf("\n[DERIVATA]\n");
	/* la derivata ha grado n - 1 */
	stampaCoefficienti(der, n - 1);
	/* Calcolo dell'integrale */
	/*
	 * integ e` dichiarato nella funzione main ma verra` modificato dalla
	 * funzione integrake che vi memorizzera` il risultato dell'elaborazione
	 */
	integrale(polinomio, n, integ);
	printf("\n[INTEGRALE]\n");
	/* l'integrale ha grado n + 1 */
	stampaCoefficienti(integ, n + 1);
	/* soluzione dell'equazione p(x) = 0 */
	printf("\n[SOLUZIONE]\n");
	printf("%.6lf\n", soluzione(polinomio, n));
	return 0;
}

