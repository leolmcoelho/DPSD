#pragma once
#ifndef SALVARARQUIVO_H_INCLUDED
#define SALVARARQUIVO_H_INCLUDED
#include <time.h>
#include <string>
using namespace std;
void salvar_arquivo_fprintf(double Volume_Amostra, double Porosidade1, double Porosidade2,
    double* Diametros, vector <long long int> Voxels_por_Raio, double* PSD, double* PSDE, short int rcm, double Tempo);

void salvar_arquivo_cpp(double Volume_Amostra, double Porosidade1,
    double* Diametros, vector <long long int> Voxels_por_Raio, double* PSD, short int rcm, double Tempo);

#endif // SALVAR_ARQUIVO_H_INCLUDED