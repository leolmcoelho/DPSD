#define _CRT_SECURE_NO_DEPRECATE
#define CLOCKS_PER_SEC

#include "LeituraConfiguracao.h"

vector<double> leitura_configuracao()
{
	FILE* arquivo;
	int i, tamanho;
	char Linha[150];
	double a2, b2, c2, TP;

	arquivo = fopen("Configuracao_do_Stack.txt", "rt");
	if (arquivo == NULL)
		printf("Erro na abertura do arquivo\n");


	fgets(Linha, 150, arquivo);
	fgets(Linha, 150, arquivo);
	fgets(Linha, 150, arquivo);
	fscanf(arquivo, "%lf", &a2);
	a2 = a2 - 1;
	fgets(Linha, 150, arquivo);
	fgets(Linha, 150, arquivo);
	fscanf(arquivo, "%lf", &b2);
	b2 = b2 - 1;
	fgets(Linha, 150, arquivo);
	fgets(Linha, 150, arquivo);
	fscanf(arquivo, "%lf", &c2);
	c2 = c2 - 1;
	fgets(Linha, 150, arquivo);
	fgets(Linha, 150, arquivo);
	//fgets(Linha, 150, arquivo);
	fscanf(arquivo, "%lf", &TP);
	//TP = TP - 1;


	vector <double> results{ a2, b2, c2, TP };
	/*printf("Valor de a2: %lf\n", a2);
	printf("Valor de b2: %lf\n", b2);
	printf("Valor de c2: %lf\n", c2);
	printf("Valor de TP: %2.0lf\n", TP);*/

	return results;
}