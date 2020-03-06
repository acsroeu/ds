#include <stdio.h>
#include <malloc.h>

int* calcul1(int nrL, int nrC, int** matr)
{
	int i, j, rez[3];
	for(i = 0; i < nrL; i++) 
	{
		rez[i] = 0;
		for(j = 0; j < nrC; j++)
			rez[i] = rez[i] + matr[i][j];
	}
	return rez;
}

int* calcul2(int nrL, int nrC, int** matr)
{
	int i, j;int* rez = NULL;
	rez = (int*)malloc(nrL * sizeof(int));
	for(i = 0; i < nrL; i++) 
	{
		rez[i] = 0;
		for(j = 0; j < nrC; j++)
			rez[i] = rez[i] + matr[i][j];
	}
	return rez;
}

void calcul3(int nrL, int nrC, int** matr, int* rez)
{
	int i, j;//int* rez = NULL;
	rez = (int*)malloc(nrL * sizeof(int));
	for(i = 0; i < nrL; i++) 
	{
		rez[i] = 0;
		for(j = 0; j < nrC; j++)
			rez[i] = rez[i] + matr[i][j];
	}
	return;
}

void calcul4(int nrL, int nrC, int** matr, int** rez)
{
	int i, j;//int* rez = NULL;
	(*rez) = (int*)malloc(nrL * sizeof(int));
	for(i = 0; i < nrL; i++) 
	{
		(*rez)[i] = 0;
		for(j = 0; j < nrC; j++)
			(*rez)[i] = (*rez)[i] + matr[i][j];
	}
	return;
}

int main()
{
	int nrMasini = 0, nrZile = 0, i = 0, j = 0;
	//int matrC[3][5];
	int** matrC = NULL;
	int* rezC = NULL;

	printf("nrMasini = "); scanf("%d", &nrMasini);
	printf("nrZile = "); scanf("%d", &nrZile);

	matrC = (int**)malloc(nrMasini * sizeof(int*));
	for(i = 0; i < nrMasini; i++)
	{
		matrC[i] = (int*)malloc(nrZile * sizeof(int));
	}

	for(i = 0; i < nrMasini; i++)
	{
		for(j = 0; j < nrZile; j++)
		{
			printf("matr[%d][%d] = ", i, j);
			scanf("%d", &matrC[i][j]);
		}
	}
	//while(1)
	{
	rezC = calcul1(nrMasini, nrZile, matrC);
	for(i = 0; i < nrMasini; i++)
	{
		printf("rezc[%d] = %d", i, rezC[i]);
	}

	rezC = calcul2(nrMasini, nrZile, matrC);
	for(i = 0; i < nrMasini; i++)
	{
		printf("rezc[%d] = %d", i, rezC[i]);
	}
	
    calcul3(nrMasini, nrZile, matrC, rezC);
	for(i = 0; i < nrMasini; i++)
	{
		printf("rezc[%d] = %d", i, rezC[i]);
	}
	

	//while(1)
	//{
	calcul4(nrMasini, nrZile, matrC, &rezC);
	for(i = 0; i < nrMasini; i++)
	{
		printf("rezc[%d] = %d", i, rezC[i]);
	}
	//}
	return 0;
}









