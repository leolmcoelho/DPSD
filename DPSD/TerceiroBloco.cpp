//#include "pch.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
using namespace std;

//long long int * terceiro_bloco(short int rcm, short int *V1, long long int *Voxels_por_Raio, double &total_poros, long long int a1, long long int a2, long long int b1, long long int b2, long long int c1, long long int c2)
vector <long long int> terceiro_bloco(short int rcm, vector <short int> V1, vector <long long int> Voxels_por_Raio, double& total_poros, int a1, int a2, int b1, int b2, int c1, int c2)
{
	int i, j, k, r;
	//long long int aux1;
	long long int aux_calculo;
	int aux1;

	if (c2 == 0)
	{
		for (r = rcm - 1; r >= 0; r--)
		{
			for (i = a1; i <= a2; i++)
			{
				for (j = b1; j <= b2; j++)
				{
					aux1 = (i * (b2 + 1)) + j;

					if (V1[aux1] == r + 1)
					{
						Voxels_por_Raio[r] = Voxels_por_Raio[r] + 1;
					}
				}

			}
			printf("\n%d", Voxels_por_Raio[r]);
			total_poros = total_poros + Voxels_por_Raio[r];
		}
	}

	else
	{
		//Parte Tridimensional
		for (r = rcm - 1; r >= 0; r--)
		{
			for (i = a1; i <= a2; i++)
			{
				for (j = b1; j <= b2; j++)
				{
					for (k = c1; k <= c2; k++)
					{
						aux_calculo = k;
						aux1 = (aux_calculo * (a2 + 1) * (b2 + 1)) + (i * (b2 + 1)) + j;
						//aux1 = (k * (a2 + 1) * (b2 + 1)) + (i * (b2 + 1)) + j;
						if (V1[aux1] == r + 1)
						{
							Voxels_por_Raio[r] = Voxels_por_Raio[r] + 1;
						}
					}
				}
			}
			printf("\n%d", Voxels_por_Raio[r]);
			total_poros = total_poros + Voxels_por_Raio[r];
		}
	}



	printf("\nTotal de pixels de poros: %.0f\n", total_poros);
	return Voxels_por_Raio;
}