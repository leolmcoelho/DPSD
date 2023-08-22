//#include "pch.h"
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <time.h>
//#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void salvar_arquivo_fprintf(double Volume_Amostra, double Porosidade1, double Porosidade2,
    double* Diametros, vector <long long int> Voxels_por_Raio, double* PSD, double* PSDE, short int rcm, double Tempo)
{
    printf("Volume da Amostra: %");
    printf("Volume Total da Amostra: %f\n", Volume_Amostra);
    printf("Porosidade Digital da Amostra (método 1): %f\n", Porosidade1);
    printf("Porosidade Digital da Amostra (método 2): %f\n", Porosidade2);
    printf("\nDADOS DE DISTRIBUIÇÃO DE TAMANHO DE POROS\n");
    printf("O maior diâmetro equivalente é de: %f\n", rcm - 0.5);

    printf("Diâmetros Equivalentes:\n");
    printf("D = [%f, ..., %f]\n", Diametros[0], Diametros[rcm - 1]);

    printf("Voxels por Diâmetros Equivalentes:\n");
    printf("V(DE) =  [%lld, ..., %lld]\n", Voxels_por_Raio[0], Voxels_por_Raio[rcm - 1]);

    printf("Distribuição de Tamanho de Poros:\n");
    printf("PSD =  [%f, ..., %f]\n", PSD[0], PSD[rcm - 1]);

    printf("Distribuição de Tamanho de Poros (Esferas):\n");
    printf("PSDE =  [%f, ..., %f]\n", PSDE[0], PSDE[rcm - 1]);
    FILE* arquivo2;

    arquivo2 = fopen("Resultados_LVA12.txt", "wt");
    fprintf(arquivo2, "Resultados de PSD da amostra LVA na resolução de 30 um.\n");
    fprintf(arquivo2, "Tempo de execução do código: %gs.\n", Tempo);
    fprintf(arquivo2, "Volume Total da Amostra: %f\n", Volume_Amostra);
    fprintf(arquivo2, "Porosidade Digital da Amostra (método 1): %f\n", Porosidade1);
    fprintf(arquivo2, "Porosidade Digital da Amostra (método 2): %f\n", Porosidade2);
    fprintf(arquivo2, "\nDADOS DE DISTRIBUIÇÃO DE TAMANHO DE POROS\n");
    fprintf(arquivo2, "O maior diâmetro equivalente é de: %f\n", rcm - 0.5);

    fprintf(arquivo2, "Diâmetros Equivalentes:\n");
    fprintf(arquivo2, "D = [%f ", Diametros[0]);
    for (int i = 1; i <= rcm - 2; i++)
    {
        fprintf(arquivo2, "%f ", Diametros[i]);
    }
    fprintf(arquivo2, "%f];\n", Diametros[rcm - 1]);

    fprintf(arquivo2, "Voxels por Diâmetros Equivalentes:\n");
    fprintf(arquivo2, "V(DE) = [%lld ", Voxels_por_Raio[0]);
    for (int i = 1; i <= rcm - 2; i++)
    {
        fprintf(arquivo2, "%lld ", Voxels_por_Raio[i]);
    }
    fprintf(arquivo2, "%lld];\n", Voxels_por_Raio[rcm - 1]);

    fprintf(arquivo2, "Distribuição de Tamanho de Poros:\n");
    fprintf(arquivo2, "PSD = [%f ", PSD[0]);
    for (int i = 1; i <= rcm - 2; i++)
    {
        fprintf(arquivo2, "%f ", PSD[i]);
    }
    fprintf(arquivo2, "%f];\n", PSD[rcm - 1]);

    fprintf(arquivo2, "Distribuição de Tamanho de Poros (Esferas):\n");
    fprintf(arquivo2, "PSD = [%f ", PSDE[0]);
    for (int i = 1; i <= rcm - 2; i++)
    {
        fprintf(arquivo2, "%f ", PSDE[i]);
    }
    fprintf(arquivo2, "%f];\n", PSDE[rcm - 1]);

    fclose(arquivo2);
}

void salvar_arquivo_cpp(double Volume_Amostra, double Porosidade1,
    double* Diametros, vector <long long int> Voxels_por_Raio, double* PSD, short int rcm, double Tempo)
{
    string arquivo_saida = "Resultados_Teste_42.txt";
    ofstream arquivo(arquivo_saida.c_str());
    if (arquivo.is_open())
    {
        arquivo << "Resultados de PSD da amostra LVA na resolução de 12 um." << endl;
        //arquivo<<"Tempo de execução do código: "<<Tempo<<endl;
        arquivo << "Volume Total da Amostra: " << Volume_Amostra << endl;
        arquivo << "Porosidade Digital da Amostra (método 1): " << Porosidade1 << endl;
        arquivo << endl << "DADOS DE DISTRIBUIÇÃO DE TAMANHO DE POROS" << endl;
        arquivo << "O maior diâmetro equivalente é de: " << (rcm - 0.5) << endl;
        arquivo << "Diâmetros Equivalentes:" << endl;
        arquivo << "D = [" << Diametros[0];
        for (int i = 1; i <= rcm - 1; i++)
        {
            arquivo << " " << Diametros[i];
        }
        arquivo << "];" << endl;

        arquivo << "Voxels por Diâmetros Equivalentes:" << endl;
        arquivo << "V(DE) = [" << Voxels_por_Raio[0];
        for (int i = 1; i <= rcm - 1; i++)
        {
            arquivo << " " << Voxels_por_Raio[i];
        }
        arquivo << "];" << endl;
        arquivo << "Distribuição de Tamanho de Poros:" << endl;
        arquivo << "PSD = [" << PSD[0];
        for (int i = 1; i <= rcm - 1; i++)
        {
            arquivo << " " << PSD[i];
        }
        arquivo << "];" << endl;

        arquivo.close();
    }

}