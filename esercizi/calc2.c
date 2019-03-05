//programma che esegue le operazioni +, -, *, /, % tra due interi e restituisce errori per evidenziare operandi e operatori non validi

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int operando1;
	int operando2;
	int sel = 0;
	char op;
	int risultato;
	char s[80];

	//chiede all'utente di inserire il primo operando	
	printf("Inserisci il primo operando\n");
	fgets(s, sizeof(s), stdin);
	operando1 = atoi(s);
	
	//chiede all'utente di inserire il secondo operando
	printf("Inserisci il secondo operando\n");
	fgets(s, sizeof(s), stdin);
	operando2 = atoi(s);

	
	//chiede all'utente di inserire l'operatore
	printf("Inserisci il numero relativo all'operazione da svolgere\n");
	printf("1) addizione\n");
	printf("2) sottrazione\n");
	printf("3) moltiplicazione\n");
	printf("4) divisione\n");
	printf("5) modulo\n");
	fgets(s, sizeof(s), stdin);
	sel = atoi(s);

	switch (sel) {
		case 1:		//addizione
			risultato = operando1 + operando2;
			op = '+';
			break;
		case 2:		//sottrazione
			risultato = operando1 - operando2;
			op = '-';
			break;
		case 3:		//moltiplicazione
			risultato = operando1 * operando2;
			op = '*';
			break;
		case 4:		//divisione con controllo divisione per zero
			if ((operando2 != 0)) {
				risultato = operando1 / operando2;
				op = ':';
			}			
			else {
				printf("ERRORE: impossibile eseguire una divisione per 0!\n");
				return 1;
			}
			break;
		case 5:		//modulo con controllo divisione per zero
			if ((operando2 != 0)) {
				risultato = operando1 % operando2;
				op = '%';
			}	
			else {
			printf("ERRORE: impossibile eseguire una divisione per 0!\n");
				return 1;
			}
			break;
		default:
			printf("ERRORE: operando non valido!\n");
			return 1;
	}

	//stampa il risultato
		printf("%d %c %d = %d\n", operando1, op, operando2, risultato);
	return 0;
}
