#pragma once
#ifndef TERCEIROBLOCO_H_INCLUDED
#define TERCEIROBLOCO_H_INCLUDED
#include <string>

using namespace std;

//long long int * terceiro_bloco(short int rcm, short int *V1, long long int *Voxels_por_Raio, double &total_poros, long long int a1, long long int a2, long long int b1, long long int b2, long long int c1, long long int c2);
vector <long long int> terceiro_bloco(short int rcm, vector <short int> V1, vector <long long int> Voxels_por_Raio, double& total_poros, int a1, int a2, int b1, int b2, int c1, int c2);

#endif // TERCEIROBLOCO_H_INCLUDED