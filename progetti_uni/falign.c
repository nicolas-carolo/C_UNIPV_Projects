//NON FUNZIONE!!! revisionare a casa!

#include <stdio.h>
#include <stdlib.h>

void falign(FILE *infile, FILE *outfile, int maxcol);

int main(int argc, char *argv[])
{
	FILE *fp;
	int maxcol, i;

	if (argc != 3){
		printf("Uso: falign file colonne\n");
		return 1;
	}

	maxcol = atoi(argv[2]);
	if (!(fp = fopen(argv[1], "r"))) {
		printf("Errore nell'apertura del file %s\n", argv[1]);
		return 1;
	}

	for (i = 1; i <= maxcol; i++) {
		printf("%d", i % 10);
	}
	putc('\n', stdout);
	
	falign(fp, stdout, maxcol);
	fclose(fp);

	return 0;
}


void falign(FILE *infile, FILE *outfile, int maxcol)
{
	char ch;
	int col = 0;
	
	while ((ch = getc(infile)) != EOF) {
		if (ch == '\n')
			putc(' ', outfile);
		else
			putc(ch, outfile);
	
		++col;

		if (col >= maxcol) {
			putc('\n', outfile);
			col = 0;
		}
	}
	putc('\n', outfile);
}
