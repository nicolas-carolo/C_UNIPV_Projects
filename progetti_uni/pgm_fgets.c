#include <stdio.h>

#define MAX_LEN (1024)
#define MAX_LEVEL (256)

struct immagine {
	int magic_number;		//numero magico
	int max_gray_level;		//massimo livello di grigio
	int larg, alt;			//larghezza e altezza [pixel]
	int istogramma[MAX_LEVEL];	//vettore contenente l'istogramma
};


int pgm_istogramma(struct immagine *pgm, FILE *infile)
{
	int n, i;
	char buf[MAX_LEN];
	int v[10];

	for (i = 0; i < MAX_LEVEL; i++)
		pgm->istogramma[i] = 0;

	fgets(buf, sizeof(buf), infile);
	n = sscanf(buf, "P%i", &pgm->magic_number);
	if ((n != 1) || (pgm->magic_number != 2)) return 1;

	fgets(buf, sizeof(buf), infile);
	if (sscanf(buf, "%i %i", &pgm->larg, &pgm->alt) != 2) return 1;

	fgets(buf, sizeof(buf), infile);
	if (sscanf(buf, "%i", &pgm->max_gray_level) != 1) return 1;

	while (fgets(buf,sizeof(buf), infile)) {
		n = sscanf(buf, "%i %i %i %i %i %i %i %i %i %i", &v[0], &v[1], &v[2], &v[3], &v[4], &v[5], &v[6], &v[7], &v[8], &v[9]);

		for (i = 0; i < n; i++)
			(pgm->istogramma[v[i]])++;
	}
	return 0;
}


void print_istogramma(struct immagine *pgm, FILE *outfile)
{
	int livello;
	for (livello = 0; livello <= pgm->max_gray_level; livello++)
		fprintf(outfile, "%3i: %i\n", livello, pgm->istogramma[livello]);
}

int main(int argc, char *argv[])
{
	struct immagine pgm;
	FILE *infile;

	if (argc != 2) {
		printf("uso: %s <nome_file_pgm>\n", argv[0]);
		return 1;
	}
	if (!(infile = fopen(argv[1], "r"))) {
		printf("ERRORE nell'aperura di %s\n", argv[1]);
		return 1;
	}
	if (pgm_istogramma(&pgm, infile) != 0) {
		puts("ERRORE nella lettura del file");
		return 1;
	}
	print_istogramma(&pgm, stdout);
	return 0;
}
