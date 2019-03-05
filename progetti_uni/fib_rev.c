#include <stdio.h>
#include <stdlib.h>

#define MAXVAL 20

int main()
{
	char s[80];
	int num[MAXVAL];
	int i, max;

	fgets(s, sizeof(s), stdin);
	max = atoi(s);
	if (max > MAXVAL)
		max = MAXVAL;
	
	num[0] = 1;
	num[1] = 1;

	for (i = 2; i < max; i++) {
		num[1] = num[i - 1] + num [i - 2];
	}

	for (i = max - 1; i >= 0; i--) {
		printf("%d\n", num[i]);
	}

	return 0; 


}
