// PSD64-bits_SF.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#define _CRT_SECURE_NO_DEPRECATE
#define CLOCKS_PER_SEC


#include "DPSD.h"



int main(int argc, char** argv)
{
	string nome_arquivo = "Arquivo de Leitura.txt";
	
	//============= Parametros Globais ============
	bool poro = 1;
	bool matriz = 0;

	long long int n;

	clock_t Ticks[7];

	int total, raio, centrox, centroy, cont, mark, l;
	int cc, cont2, r;
	double TP, AA, BB, CC, DD, EE, FF;
	short int rcm;
	int a1, a2, b1, b2, c1, c2, aa, bb, i, j, k;
	long long int Quantidade_Pixels_Regiao_Interesse;
	a1 = 0;
	b1 = 0;
	c1 = 0;
	
	//==================================================

	vector <double> aux;
	aux = leitura_configuracao();
	a2 = (int)aux[0];
	b2 = (int)aux[1];
	c2 = (int)aux[2];
	TP = (int)aux[3];

	cout << a2 << endl;

	Ticks[0] = clock();
	vector <bool> V;
	V = leitura_arquivo(nome_arquivo);
	n = V.size();
	Ticks[1] = clock();
	double Tempo = (Ticks[1] - Ticks[0]) / CLOCKS_PER_SEC;
	printf("Tempo gasto na leitura do arquivo: %gs.\n", Tempo);

	
	V = Filtro(matriz, V, a1, a2, b1, b2, c1, c2, Quantidade_Pixels_Regiao_Interesse);
	Ticks[2] = clock();
	Tempo = (Ticks[2] - Ticks[1]) / CLOCKS_PER_SEC;
	printf("\nTempo gasto na execucao do filtro: %gs.\n", Tempo);


	vector <short int> V0(n);

	rcm = 0;
	
	V0 = identificacao_raio_critico(poro, matriz, V, V0, a1, a2, b1, b2, c1, c2, rcm, n);
	Ticks[3] = clock();
	Tempo = (Ticks[3] - Ticks[2]) / CLOCKS_PER_SEC;
	printf("\nTempo gasto no bloco de Rc: %gs.\n", Tempo);
	printf("\nO valor do raio critico e' de: %d \n", rcm - 1);
	V.clear();

	//Segundo Bloco
	vector <short int> V1(n);
	V1 = associacao_pixels_aos_raios_criticos(rcm, V0, V1, a1, a2, b1, b2, c1, c2);

	V0.clear();
	Ticks[4] = clock();
	Tempo = (Ticks[4] - Ticks[3]) / CLOCKS_PER_SEC;
	printf("\nTempo gasto no segundo bloco: %gs.\n", Tempo);
	double total_poros = 0;

	vector <long long int> Voxels_por_Raio(n);
	Voxels_por_Raio = terceiro_bloco(rcm, V1, Voxels_por_Raio, total_poros, a1, a2, b1, b2, c1, c2);

	V1.clear();
	Ticks[5] = clock();
	Tempo = (Ticks[5] - Ticks[4]) / CLOCKS_PER_SEC;
	printf("\nTempo gasto no terceiro bloco: %gs.\n", Tempo);

	//Início do cálculo do PSD
	double* PSD, * PSDE, * Volume_por_Voxel, * Diametros, Volume_Amostra, pi = 3.1416, Volume_Poroso_Esferas, Porosidade1, Porosidade2;
	PSD = (double*)calloc(rcm, sizeof(double));
	PSDE = (double*)calloc(rcm, sizeof(double));
	Volume_por_Voxel = (double*)calloc(rcm, sizeof(double));
	Diametros = (double*)calloc(rcm, sizeof(double));

	Volume_Amostra = Quantidade_Pixels_Regiao_Interesse * TP * TP * TP;

	int Pixels_por_Esfera[101] = { 1, 7, 33, 123, 257, 515, 925, 1419, 2109, 3071, 4169, 5575, 7153, 9171, 11513, 14147, 17077, 20479, 24405, 28671, 33401, 38911, 44473, 50883, 57777, 65267, 73525, 82519, 91965, 101943, 113081, 124487, 137065, 150555, 164517, 179579, 195269, 212095, 229549, 248439, 267761, 288359, 310177, 332779, 356637, 381915, 407597, 434551, 462781, 492567, 523305, 555491, 588817, 623443, 659757, 696507, 735317, 775775, 816577, 860079, 904089, 950675, 997841, 1047331, 1097917, 1149651, 1204469, 1259303, 1316425, 1376263, 1436385, 1498755, 1562465, 1628755, 1697437, 1767063, 1838661, 1912319, 1987441, 2064775, 2143641, 2225667, 2308577, 2395091, 2482213, 2571711, 2663925, 2758343, 2854025, 2951647, 3053617, 3156603, 3261029, 3369443, 3478573, 3590863, 3705093, 3821855, 3941729, 4064563, 4187857 };
	Volume_Poroso_Esferas = 0;
	printf("PSD:\n");
	for (i = 0; i <= rcm - 1; i++)
	{
		PSD[i] = Voxels_por_Raio[i] * TP * TP * TP / Volume_Amostra * 100;
		printf("%f\t%d\n", PSD[i], i);
		//Volume_por_Voxel[i] = 4 / 3 * pi * (i + 0.5) * TP * (i + 0.5) * TP * (i + 0.5) * TP / Pixels_por_Esfera[i];
		Diametros[i] = 2 * (i + 0.5) * TP;
		//printf("%f\t%d\n", Diametros[i], i);
	}

	Porosidade1 = total_poros / Quantidade_Pixels_Regiao_Interesse;
	//Porosidade2 = Volume_Poroso_Esferas / Volume_Amostra;
	printf("\nPorosidade da amostra: %lf\n", Porosidade1);

	//Impressão dos resultados em arquivo
	salvar_arquivo_cpp(Volume_Amostra, Porosidade1,
		Diametros, Voxels_por_Raio, PSD, rcm, Tempo);

	Ticks[6] = clock();
	Tempo = (Ticks[6] - Ticks[0]) / CLOCKS_PER_SEC;
	printf("\nTempo total de processamento: %gs.\n\n", Tempo);

	Voxels_por_Raio.clear();
	system("PAUSE");
	return 0;
}