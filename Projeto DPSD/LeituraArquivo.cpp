#define _CRT_SECURE_NO_DEPRECATE
#define CLOCKS_PER_SEC

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;

vector <bool> leitura_arquivo(string nome_arquivo)
{
	FILE* arquivo; 
	long long int n, i;
	bool aux;


	arquivo = fopen(nome_arquivo.c_str(), "rt");
	if (arquivo == NULL)
		printf("Erro na abertura do arquivo %s\n",nome_arquivo.c_str());
	
	fscanf(arquivo, "%lld", &n);
	printf("Valor de n: %lld\n", n);
	
	vector <bool> V(n);

	i = 0;
	while (!feof(arquivo))
	{
		fscanf(arquivo, "%d", &aux);
		V[i] = aux;
		i++;
	}
	printf("Tamanho de V: %lld\n", i);


	fclose(arquivo);
	return V;
}