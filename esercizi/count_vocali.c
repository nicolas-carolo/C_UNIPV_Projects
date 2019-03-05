//programma che legge da standard input una sequenza di stringhe. Il programma deve determinare e stampare quante vocali sono state inserite, sia maiuscole che minuscole. il programma deve terminare quando viene inserita una stringa vuota.

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char s[1000];
	int i;
	int count_a = 0;
	int count_e = 0;
	int count_i = 0;
	int count_o = 0;	
	int count_u = 0;

	fgets(s, sizeof(s), stdin);
	
	while (s[0] != '\n') {
		for (i = 0; s[i] != '\n' ; i++) {
			if (s[i] == 'a' || s[i] == 'A') {
				count_a++;
			}

			if (s[i] == 'e' || s[i] == 'E') {
				count_e++;
			}

			if (s[i] == 'i' || s[i] == 'I') {
				count_i++;
			}

			if (s[i] == 'o' || s[i] == 'O') {
				count_o++;
			}

			if (s[i] == 'u' || s[i] == 'U') {
				count_u++;
			}
		}

		fgets(s, sizeof(s), stdin);
	}

	printf("a: %d\n", count_a);	
	printf("e: %d\n", count_e);
	printf("i: %d\n", count_i);
	printf("o: %d\n", count_o);
	printf("u: %d\n", count_u);

	return 0;
}
