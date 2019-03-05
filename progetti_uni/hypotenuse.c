#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double leggi_double(void);
double quad(double num);
double ipot(double cat1, double cat2);

int main()
{
	double a, b;

	a = leggi_double();
	b = leggi_double();

	printf("Ipotenusa: %lf\n", ipot(a, b));

	return 0;
}


double leggi_double(void)
{
	char buf[100];
	fgets(buf, sizeof(buf), stdin);
	return atof(buf);
}


double quad(double num)
{
	return num * num;
}


double ipot(double cat1, double cat2)
{
	return sqrt(quad(cat1) + quad(cat2));
}
