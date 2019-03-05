#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FNAME "outfile"
#define MAX_DIM 0xffff

int split_file(FILE *fin, int dim)
{
	size_t nread;
	int count = 0;
	char fname[30];
	char buffer[MAX_DIM];
	FILE *fout;

	if (dim <= 0 || dim > MAX_DIM)
		return -1;
	do {
		nread = fread(buffer, 1, dim, fin);
		if (nread > 0) {
			sprintf(fname, "%s%d%s", FNAME, count, ".split");
			if (!(fout = fopen(fname, "w"))) {
				return -1;
			}
			fwrite(buffer, 1, nread, fout);
			fclose(fout);
			count++;
		}
	} while (nread == dim);
	return 0;
}

int main(int argc, char *argv[])
{
	FILE *fin;
	int dim;
	
	if (argc != 3) {
		printf("Utilizzo: split_file infile dimensione\n");
		return -1;
	}
	
	if (!(fin = fopen(argv[1], "r"))) {
		printf("Impossibile aprire il file di input.\n");
		return -1;
	}
	dim = atoi(argv[2]);

	return split_file(fin , dim);
}
