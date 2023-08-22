#pragma once
#ifndef FILTRO_H_INCLUDED
#define FILTRO_H_INCLUDED
#include <string>

using namespace std;

//void Filtro(bool matriz, bool*V, long long int a1, long long int a2, long long int b1, long long int b2, long long int c1, long long int c2, long long int &Quantidade_Pixels_Regiao_Interesse);
vector <bool> Filtro(bool matriz, vector <bool> V, int a1, int a2, int b1, int b2, int c1, int c2, long long int& Quantidade_Pixels_Regiao_Interesse);

#endif // FILTRO_H_INCLUDED