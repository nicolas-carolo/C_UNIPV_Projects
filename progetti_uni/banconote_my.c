#include <stdio.h>

//programma per il calcolo delle banconote

int main ()
{
	int euro = 988;
	int b50;
	int b20;
	int b10;
	int b5;
	int m2;
	int m1;

	printf("Per raggiungere la quota di %i euro, servono:\n", euro);
	
	
	b50 = euro / 50;
	printf("%i banconote da 50\n", b50);
	euro = euro % 50;
	
	b20 = euro / 20;
	printf("%i banconote da 20\n", b20);
	euro = euro % 20;
	
	b10 = euro / 10;
	printf("%i banconote da 10\n", b10);
	euro = euro % 10;

	b5 = euro / 5;
	printf("%i banconote da 5\n", b5);
	euro = euro % 5;

	m2 = euro / 2;
	printf("%i monete da 2\n", m2);
	euro = euro % 2;

	m1 = euro / 1;
	printf("%i monete da 1\n", m1);
	euro = euro % 1;
	
	return 0;

}
