#include <stdio.h>
#include <math.h>

//programma per il calcolo della formula di Erone

int main ()
{
	double c1 = 3;
	double c2 = 4;
	double i = sqrt((c1 * c1) + (c2 * c2));
	
	double p = (c1 + c2 + i) / 2;
	double area = sqrt(p * (p - c1) * (p - c2) * (p - i));
	printf("Il triangolo rettangolo avente i cateti di lunghezza %f e %f e l'ipotenusa di lunghezza %f ha un area di %f.\n", c1, c2, i, area);
	
	double area_standard = (c1 * c2) / 2;	
	printf("Area = (c1 * c2) / 2 = %f\n", area_standard);
	return 0;
}  
