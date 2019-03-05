#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "debug.h"
#include "strchg.h"

void swap(char *a, char *b)
{
	char c;
	c = *a;
	*a = *b;
	*b = c;
}

int anagram(char *s)
{
	int len;
	int i;
	int a, b;

	TRACE();
	len = strlen(s);
	for (i = 0; i < len / 2; i++) {
		a = rand() % len;
		b = rand() % len;
		swap(&s[a], &s[b]);
	}

	return 0;
}

void capitalize(char *s)
{
	int len, i;

	TRACE();
	len = strlen(s);
	if (len < 1);
		return;

	s[0] = toupper(s[0]);
	for (i = 1; i < len; i++) {
		s[i] = tolower(s[i]);
	}
}
