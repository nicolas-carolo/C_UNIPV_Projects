//programma che legge interi. Il programma conta il numero di valori dispari immessi e termina quando il conteggio arriva a 10. Al termine viene stampato il numero di letture effettuate

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char s[80];
	int n;
	int letture = 0;
	int resto;
	int dispari = 0;

	fgets(s, sizeof(s), stdin);
	n = atoi(s);
	resto = n % 2;
	if (resto != 0) {
		dispari++;
		letture++;
	}

	while (dispari < 10) {
		fgets(s, sizeof(s), stdin);
		n = atoi(s);
		resto = n % 2;
		
		if (resto != 0) {
		dispari++;
		}
		
		letture++;
		
	}
	
	printf("Sono state eseguite %d letture\n", letture);
	return 0;
}
