# -*- coding: utf-8 -*-
"""
Created on Sat Sep  7 17:24:34 2019

@author: Adriano Rocha
"""


import numpy  as np
from PIL import Image
import time


def PixelValues (a2, b2, Delta_Ordem, Nome_Comum_dos_Arquivos,
                 Numero_Primeira_Imagem, Extensao):
    Numero_da_Imagem = str(Numero_Primeira_Imagem)
    Nome_do_Arquivo  = Nome_Comum_dos_Arquivos[:-1]
    
    j = 0
    while (j < Delta_Ordem):
        Nome_do_Arquivo  = Nome_do_Arquivo + "0"
        j = j + 1
    Nome_do_Arquivo  = Nome_do_Arquivo + Numero_da_Imagem + Extensao
    im =Image.open(Nome_do_Arquivo )
    C = np.zeros((b2+1,a2+1))
    C[:,:] = np.array(im)
    pixel1 = int(C[0,0])
    
    contPixel1 = 0
    contPixel2 = 0
    contPixel3 = 0
    flag = 0
    pixel2 = -1
    for j in range (a1,a2+1):
        for k in range (b1,b2+1):
            aux = int(C[k,j])
            if (aux!=pixel1 and flag==0):
                pixel2 = aux
                contPixel2 += 1
                flag = 1
            elif (aux==pixel2):
                contPixel2 += 1
            elif (aux!=pixel1 and aux!=pixel2):
                contPixel3 +=1
    if(contPixel2>contPixel3 and contPixel3!=0):
        value2 = 0
        value3 = 1
    else:
        value2 = 1
        value3 = 0
        
    return pixel1, pixel2, value2, value3


#Início da rotina de geração de arquivo de leitura
inicio = time.time()

a1=0;
b1=0;
c1=0;

arquivo_configuracao = open('Configuracao_do_Stack.txt','r')
linhas = arquivo_configuracao.readlines()
a2 = int(linhas[3])-1;
b2 = int(linhas[5])-1;
c2 = int(linhas[7])-1;

Nome_Comum_dos_Arquivos  = linhas[12]
Extensao = linhas[18]

Numero_Primeira_Imagem = int(linhas[14])
Numero_Ultima_Imagem = int(linhas[16])

#Cálculo da ordem de grandeza dos números das imagens
if(Numero_Primeira_Imagem == 0):
    Ordem_Primeira_Imagem = 0
else:
    j=0
    while (Numero_Primeira_Imagem/pow(10,j)>=10):
        j = j + 1
    Ordem_Primeira_Imagem = j

j=0
while (Numero_Ultima_Imagem/pow(10,j)>=10):
    j = j + 1
Ordem_Ultima_Imagem = j

Delta_Ordem = Ordem_Ultima_Imagem - Ordem_Primeira_Imagem
Limite_de_Ordem = [Delta_Ordem]
if (Delta_Ordem > 0):    
    for i in range (1,(Delta_Ordem)+ 1):
        Limite_de_Ordem[i-1] = pow(10,(Ordem_Primeira_Imagem + i))
        #print(Limite_de_Ordem[i-1])
        #print(i)
else:
    Limite_de_Ordem[0] = -1


pixel1, pixel2, value2, value3 = PixelValues(a2, b2, Delta_Ordem, 
                 Nome_Comum_dos_Arquivos,Numero_Primeira_Imagem,
                 Extensao)

arquivo = open('Arquivo de Leitura.txt','w')
impresso = str((a2+1)*(b2+1)*(c2+1))+"\n"
arquivo.write(impresso)

# Leitura das imagens
C = np.zeros((b2+1,a2+1))

cont = 0
cont2 = 0
cont3 = 0
contador = 0
contPrints = 0
#Nome_Comum_dos_Arquivos  = 'lva 1cm 5.3µm_al+cu__rec_bin0'
#Extensao ='.bmp'
for i in range (Numero_Primeira_Imagem,Numero_Ultima_Imagem + 1):
   print("Gerando arquivo de leitura: ",(i-Numero_Primeira_Imagem) /(Numero_Ultima_Imagem-Numero_Primeira_Imagem+1)*100,
         "%")
   Numero_da_Imagem = str(i)
   Nome_do_Arquivo  = Nome_Comum_dos_Arquivos[:-1]
   if(i == Limite_de_Ordem[contador]):
       contador = contador + 1
       Delta_Ordem = Delta_Ordem - 1
       if(contador == len(Limite_de_Ordem)):
           contador = contador - 1
   j = 0
   while (j < Delta_Ordem):
       Nome_do_Arquivo  = Nome_do_Arquivo + "0"
       j = j + 1
   Nome_do_Arquivo  = Nome_do_Arquivo + Numero_da_Imagem + Extensao
   im =Image.open(Nome_do_Arquivo )
   C[:,:] = np.array(im)
   for j in range (a1,a2+1):
       for k in range (b1,b2+1):
           aux = int(C[k,j])
           if (aux==pixel1):
               aux = 0
           elif (aux==pixel2):
               aux = value2
               cont2 += 1
           else:
               aux = value3
               cont3 += 1
               
           impresso = str(aux) + " "
           contPrints = contPrints+1
           arquivo.write(impresso)
           arquivo.close
if(i==Numero_Ultima_Imagem):
    print("Gerando arquivo de leitura:  100%")
final = time.time()
print('Tempo total para gerar arquivo de leitura: ',final - inicio)
if(value2 and cont3>0):
    print("\nPorosidade Digital Estimada: ",cont2/(cont2+cont3)*100)
elif(value2 == 0 and cont3>0):
    print("\nPorosidade Digital Estimada: ",cont3/(cont2+cont3)*100)
input("\nAperte Enter para fechar o programa...")
    