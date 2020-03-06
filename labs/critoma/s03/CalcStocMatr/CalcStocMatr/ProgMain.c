#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Produs {
	int id;
	char* nume;
	float stoc;
	float pret;
};

void calcStocPerMag(int m, int n, struct Produs*** mat, double** rez) {
	int i = 0, j = 0;
	//if(*rez != NULL) free(*rez);
	*rez = (double*)malloc(m * sizeof(double));

	for(i = 0; i < m; i++) {
		(*rez)[i] = 0;
		for(j = 0; j < n; j++) {
			(*rez)[i] += (mat[i][j]->pret * mat[i][j]->stoc);
		}
	}
}

int main(int argc, char** argv)
{
	int nrMagazine = 0; int nrProduse = 0;
	struct Produs*** matr = NULL;
	double* rezStoc = 0;
	struct Produs* part = NULL;
	char buf[10];
	int i = 0, j = 0;

	printf("nrMagazine = "); scanf("%d", &nrMagazine);
	printf("nrProduse = "); scanf("%d", &nrProduse);

	matr = (struct Produs***)malloc(nrMagazine * sizeof(struct Produs**));
	for(i = 0; i < nrMagazine; i++)
	{
		matr[i] = (struct Produs**)malloc(nrProduse * sizeof(struct Produs*));
		for(j = 0; j < nrProduse; j++) {
			part = (struct Produs*)malloc(nrProduse * sizeof(struct Produs));

			printf("matr[%d][%d].id = ", i, j); scanf("%d", &part->id);

			printf("matr[%d][%d].nume = ", i, j);
			scanf("%s", &buf);
			part->nume = (char*)malloc((strlen(buf) + 1) * sizeof(char));
			strcpy(part->nume, buf);

			printf("matr[%d][%d].stoc = ", i, j); scanf("%f", &part->stoc);
			printf("matr[%d][%d].pret = ", i, j); scanf("%f", &part->pret);

			matr[i][j] = part;
		}
	}
	while(1)
	{
	calcStocPerMag(nrMagazine, nrProduse, matr, &rezStoc);
	for(i = 0; i < nrMagazine; i++)
		printf("\n rezStoc[%d] = %lf", i, rezStoc[i]);
	}
	return 0;
}



