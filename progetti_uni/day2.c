#include <stdio.h>
#include <stdlib.h>

int main()
{
	int dxm[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	char *mese[] = {"gennaio", "febbraio", "marzo", "aprile", "maggio", "giugno", "luglio", "agosto", "settembre", "ottobre", "novembre", "dicembre"};
	char st[10];
	int m;

	fgets(st, sizeof(st), stdin);
	m = atoi(st);
	printf("Il mese di %s è composto da %i giorni\n", mese[m - 1], dxm[m - 1]);
	return 0;
}
