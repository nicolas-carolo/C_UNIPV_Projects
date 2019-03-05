//da riguardare

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int i;
	
	for(i = 0; i < argc; i++) {
		printf("arg %i/%i: \"%s\"\n", i, argc, argv[i]);
	}
	return 0;
}
