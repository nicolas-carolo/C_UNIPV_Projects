//dati il giorno del mese e il numero del mese restituisce il giorno dell'anno

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int giorno;
	int mese;

	if(argc != 3) {
		puts("ERRORE: argomenti non validi!");
		puts("Inserire prima il giorno del mese e poi il numero del mese.");
		puts("ESEMPIO: ./giorno 31 5");
		puts("per sapere il numero a cui corrisponde il 31 maggio.");
		return 1;
	}

	giorno = atoi(argv[1]);
	mese = atoi(argv[2]);

	if (giorno < 1 || giorno > 31) {
		puts("ERRORE: giorno non valido! Inserire un giorno del mese valido!");
			return 1;
	}

	if (mese < 1 || mese > 12) {
		puts("ERRORE: mese non valido! Inserire un numero compreso tra 1 e 12!");
		return 1;
	}

	//printf("%d %d\n", giorno, mese);	

	switch (mese) {
		case 1:		
			printf("Numero di giorni %d\n", giorno);
			break;
		case 2:
			if (giorno > 28) {
				puts("ERRORE: Febbraio ha solo 28 giorni!");
				return 1;
			}
			giorno = 31 + giorno;
			printf("Numero di giorni: %d\n", giorno);
			break;
		case 3:	
			giorno = 59 + giorno;	
			printf("Numero di giorni: %d\n", giorno);
			break;
		case 4:
			if (giorno > 30) {
				puts("ERRORE: Aprile ha solo 30 giorni!");
				return 1;
			}
			giorno = 90 + giorno;
			printf("Numero di giorni: %d\n", giorno);
			break;
		case 5:	
			giorno = 120 + giorno;	
			printf("Numero di giorni: %d\n", giorno);
			break;
		case 6:
			if (giorno > 30) {
				puts("ERRORE: Giugno ha solo 30 giorni!");
				return 1;
			}
			giorno = 151 + giorno;
			printf("Numero di giorni: %d\n", giorno);
			break;
		case 7:	
			giorno = 181 + giorno;	
			printf("Numero di giorni: %d\n", giorno);
			break;
		case 8:	
			giorno = 212 + giorno;	
			printf("Numero di giorni: %d\n", giorno);
			break;
		case 9:
			if (giorno > 30) {
				puts("ERRORE: Settembre ha solo 30 giorni!");
				return 1;
			}
			giorno = 243 + giorno;
			printf("Numero di giorni: %d\n", giorno);
			break;
		case 10:	
			giorno = 273 + giorno;	
			printf("Numero di giorni: %d\n", giorno);
			break;
		case 11:	
			if (giorno > 30) {
				puts("ERRORE: Novembre ha solo 30 giorni!");
				return 1;
			}
			giorno = 304 + giorno;
			printf("Numero di giorni: %d\n", giorno);
			break;
		case 12:	
			giorno = 334 + giorno;	
			printf("Numero di giorni: %d\n", giorno);
			break;
	}
	
	return 0;
}
