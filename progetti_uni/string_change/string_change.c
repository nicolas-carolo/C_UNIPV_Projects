#include <stdlib.h>
#include "debug.h"
#include "pers.h"
#include "strchg.h"

int main(int argc, char *argv[])
{
	struct pers *per;
	
	TRACE();
	srand(argc == 2 ? atoi(argv[1]) : 3);

	if (!(per = pers_alloc("Albert", "Einstein")))
		return 1;

	pers_print(per);

	TRACE();
	anagram(per->nome);
	anagram(per->cognome);
	pers_print(per);

	capitalize(per->nome);
	capitalize(per->cognome);
	pers_print(per);

	pers_free(per);
	TRACE();
	
	return 0;
}
