#ifndef _PERS_H_
#define _PERS_H_

struct pers {
	char *nome;
	char *cognome;
};

struct pers *pers_alloc(const char *nome, const char *cognome);
void pers_free(struct pers *p);
void pers_print(struct pers *p);

#endif
