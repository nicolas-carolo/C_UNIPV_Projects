#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "pers.h"

struct pers *pers_alloc(const char *nome, const char *cognome)
{
	struct pers *p;
	TRACE();

	if (!nome || !cognome)
		return NULL;

	if (!(p = malloc(sizeof(*p))))
		return NULL;

	if (!(p->nome = strdup(nome))) {
		free(p);
		return NULL;
	}

	if (!(p->cognome = strdup(cognome))) {
		free(p->nome);
		free(p);
		return NULL;
	}
	
	return p;
}

void pers_free(struct pers *p)
{
	TRACE();
	free(p->nome);
	free(p->cognome);
	free(p);
}

void pers_print(struct pers *p)
{
	TRACE();
	if (p && p->nome &&p->cognome)
		printf("%s %s\n", p->nome, p->cognome);
}
