//#include "pch.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;

//void Filtro(bool matriz, bool *V, long long int a1, long long int a2, long long int b1, long long int b2, long long int c1, long long int c2, long long int &Quantidade_Pixels_Regiao_Interesse)
vector <bool> Filtro(bool matriz, vector <bool> V, int a1, int a2, int b1, int b2, int c1, int c2, long long int& Quantidade_Pixels_Regiao_Interesse)
{
	int menor, maior, b, i, j, k, cc;
	short int* limites_linhas;
	//long long int cc, aux1, aux2, cont;
	long long int aux_calculo, aux1, aux2, cont;


	limites_linhas = (short int*)calloc((2 * (a2 + 1) * (c2 + 1)), sizeof(short int));
	short int id = 0;

	bool flag, flag2;



	for (k = c1; k <= c2; k++)
	{
		for (i = a1; i <= a2; i++)
		{

			menor = b2 + 1;
			maior = 0;
			flag = 0;
			flag2 = b = 1;


			for (j = b1; j <= b2; j++)
			{
				aux_calculo = k;
				aux1 = (aux_calculo * (a2 + 1) * (b2 + 1)) + (i * (b2 + 1)) + j;
				if (V[aux1] == matriz)
				{
					flag = 1;
					if (j < menor)
						menor = j;
					if (j > maior)
						maior = j;
				}
			}

			while (flag && (menor > 0))
			{
				b = menor - 1;

				for (cc = c1; cc <= c2; cc++)
				{
					aux_calculo = cc;
					aux1 = (aux_calculo * (a2 + 1) * (b2 + 1)) + (i * (b2 + 1)) + b;
					//printf("%d, %d, %d\n",aux1, i, k);
					if (V[aux1] == matriz)
					{
						flag2 = 0;
						menor = b;
						break;
					}
					flag2 = 1;
				}
				if (flag2 == 1)
				{
					break;
				}
			}
			while (flag && (maior < b2))
			{
				b = maior + 1;
				for (cc = c1; cc <= c2; cc++)
				{
					aux_calculo = cc;
					aux1 = (aux_calculo * (a2 + 1) * (b2 + 1)) + (i * (b2 + 1)) + b;
					if (V[aux1] == matriz)
					{
						flag2 = 0;
						maior = b;
						break;
					}
					flag2 = 1;
				}
				if (flag2 == 1)
				{
					break;
				}
			}

			if (flag == 1)
			{
				aux2 = k * a2 * 2 + i * 2;
				limites_linhas[aux2] = menor;
				aux2++;
				limites_linhas[aux2] = maior;
				aux2++;
			}
			else
			{
				aux2 = k * a2 * 2 + i * 2;
				limites_linhas[aux2] = b2 + 1;
				aux2++;
				limites_linhas[aux2] = -1;
				aux2++;

			}
		}
	}
	//cont = cont2 = 0;
	cont = 0;
	for (k = c1; k <= c2; k++)
	{
		for (i = a1; i <= a2; i++)
		{
			aux_calculo = k;
			aux2 = aux_calculo * a2 * 2 + i * 2;
			menor = limites_linhas[aux2];
			aux2++;
			maior = limites_linhas[aux2];
			for (j = b1; j <= b2; j++)
			{
				if ((j < menor) || (j > maior))
				{
					aux_calculo = k;
					aux1 = (aux_calculo * (a2 + 1) * (b2 + 1)) + (i * (b2 + 1)) + j;
					V[aux1] = matriz;
					//cont2++;
				}
				else
					cont++;

			}
		}
	}

	Quantidade_Pixels_Regiao_Interesse = cont;
	printf("Quantidade_Pixels_Regiao_Interesse: %lld", Quantidade_Pixels_Regiao_Interesse);

	return V;
}