//programma per eseguire la conversione euro-dollaro
//cambio dollaro = 1,1125

#include <stdio.h>

int main ()
{
	float euro = 100;
	float cambio = 1.1125;
	float dollaro = euro * cambio;
	printf("%f euro corrispondono a %f dollari\n", euro, dollaro);
	return 0;
}
