# -*- coding: utf-8 -*-
"""
Created on Sat Sep 7 17:24:34 2019

"""

import json
import numpy as np
from PIL import Image
import time

from gui import Config

class ImageProcessor:

    def __init__(self, config_file_path):
        self.config_file_path = config_file_path
        self.read_configuration_file()
        self.calculate_image_order()
        self.set_image_file_name()
        self.calculate_pixel_values()

    def read_configuration_file(self):
        with open(self.config_file_path, 'r') as file:
            self.config = json.load(file)

        pixels = self.config['pixels']

        arquivos = self.config['arquivo']

        self.eixoX = pixels['X']-1
        self.eixoY = pixels['Y']-1
        self.quantidade_imagens = arquivos['quantidade']-1
        self.name = arquivos['nome_comum']

        self.extension = arquivos['extensao']
        self.start_num = arquivos['primeira_imagem']
        self.end_num = arquivos['ultima_imagem']

    def calculate_image_order(self):
        self.start_order = len(str(self.start_num)) - len(str(self.start_num).lstrip('0'))
        self.end_order = len(str(self.end_num)) - len(str(self.end_num).lstrip('0'))
        self.delta_order = self.end_order - self.start_order
        self.order_limits = [pow(10, self.start_order + i)
                             for i in range(self.delta_order)] if self.delta_order > 0 else [-1]

    def set_image_file_name(self):
        file_number = str(self.start_num).zfill(self.delta_order + 1)
        self.file_name = f"{self.name[:-1]}{file_number}{self.extension}"

    def PixelValues(eixoX, eixoY, Delta_Ordem, Nome_Comum_dos_Arquivos,
                    Numero_Primeira_Imagem, Extensao):
        Numero_da_Imagem = str(Numero_Primeira_Imagem)
        Nome_do_Arquivo = Nome_Comum_dos_Arquivos[:-1]

        a1=0
        b1=0
               
        j = 0
        # Preenchendo zeros à esquerda do número da imagem
        Numero_da_Imagem_str = str(Numero_da_Imagem).zfill(Delta_Ordem + 1)
        # Montando o nome do arquivo com o número da imagem
        Nome_do_Arquivo = f"{Nome_Comum_dos_Arquivos}{Numero_da_Imagem_str}{Extensao}"
        # Abrindo a imagem
        im = Image.open(Nome_do_Arquivo)
        # Criando o array C com as dimensões especificadas
        C = np.zeros((eixoY + 1, eixoX + 1))
        # Populando o array C com os valores da imagem
        C[:, :] = np.array(im)
        # Obtendo o valor do pixel (0, 0)
        pixel1 = int(C[0, 0])


        contPixel1 = 0
        contPixel2 = 0
        contPixel3 = 0
        flag = 0
        pixel2 = -1
        for j in range(a1, eixoX+1):
            for k in range(b1, eixoY+1):
                aux = int(C[k, j])
                if (aux != pixel1 and flag == 0):
                    pixel2 = aux
                    contPixel2 += 1
                    flag = 1
                elif (aux == pixel2):
                    contPixel2 += 1
                elif (aux != pixel1 and aux != pixel2):
                    contPixel3 += 1
        if(contPixel2 > contPixel3 and contPixel3 != 0):
            value2 = 0
            value3 = 1
        else:
            value2 = 1
            value3 = 0

        return pixel1, pixel2, value2, value3

    def calculate_pixel_values(self):
        image = Image.open(self.file_name)
        arr = np.array(image)
        self.pixel1 = int(arr[0, 0])

        contPixel1 = 0
        contPixel2 = 0
        contPixel3 = 0
        flag = 0
        pixel2 = -1

        for j in range(self.a1, self.eixoX + 1):
            for k in range(self.b1, self.eixoY + 1):
                aux = int(arr[k, j])
                if aux != self.pixel1 and flag == 0:
                    pixel2 = aux
                    contPixel2 += 1
                    flag = 1
                elif aux == pixel2:
                    contPixel2 += 1
                elif aux != pixel1 and aux != pixel2:
                    contPixel3 += 1

        if contPixel2 > contPixel3 and contPixel3 != 0:
            self.value2 = 0
            self.value3 = 1
        else:
            self.value2 = 1
            self.value3 = 0

    def generate_read_file(self):
        with open('Arquivo de Leitura.txt', 'w') as file:
            total_pixels = (self.eixoX + 1) * (self.eixoY + 1) * (self.quantidade_imagens + 1)
