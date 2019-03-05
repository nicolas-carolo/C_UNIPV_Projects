#include <stdio.h>

int main()
{
	int importo = 1028;
	int b50,b20,b10,b5,m2,m1;
	int resto;
	b50 = importo / 50;
	resto = importo % 50;
	b20 = resto / 20;
	resto = resto % 20;
	b10 = resto / 10;
	resto = resto % 10;
	b5 = resto / 5;
	resto = resto % 5;
	m2 = resto / 2;
	m1 = resto % 2;
	printf("importo totale: %d\n",importo);
	printf("%d banconote da 50 euro\n",b50);
	printf("%d banconote da 20 euro\n",b20);
	printf("%d banconote da 10 euro\n",b10);
	printf("%d banconote da 5 euro\n",b5);
	printf("%d monete da 2 euro\n",m2);
	printf("%d monete da 1 euro\n",m1);
	return 0;
}
