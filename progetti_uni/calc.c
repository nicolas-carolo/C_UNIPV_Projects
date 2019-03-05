//programma che svolge operazioni elementari tra due numeri in virgola mobile

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char s[80];
	double n1, n2, r;
	int sel;
	char op;

	puts("Inserire due valori separati da invio:");
	fgets(s, sizeof(s),stdin);
	n1 = atof(s);
	fgets(s, sizeof(s), stdin);
	n2 = atof(s);
	puts("Operazione: 1) somma                2) sottrazione");
	puts("            3) moltiplicazione      4) divisione");
	fgets(s, sizeof(s), stdin);
	sel = atoi(s);

	switch (sel) {
		case 1:
			r = n1 + n2;
			op = '+';
			break;
		case 2:
			r = n1 - n2;
			op = '-';
			break;
		case 3:
			r = n1 * n2;
			op = '*';
			break;
		case 4: 
			r = (double)n1 / n2;
			op = ':';
			break;
		default:
			return 1;
		}
	
	printf("%lf %c %lf = %lf\n", n1, op, n2, r);
	
	return 0;
}
			










