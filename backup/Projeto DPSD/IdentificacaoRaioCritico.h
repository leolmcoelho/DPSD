#pragma once
#ifndef IDENTIFICACAORAIOCRITICO_H_INCLUDED
#define IDENTIFICACAORAIOCRITICO_H_INCLUDED
#include <string>

vector <short int> identificacao_raio_critico(bool poro, bool matriz, vector <bool> V, vector <short int> V0, int a1, int a2,
	int b1, int b2, int c1, int c2, short int& rcm, long long int n);

#endif // IDENTIFICACAORAIOCRITICO_H_INCLUDED