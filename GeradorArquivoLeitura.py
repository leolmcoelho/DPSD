import json
import numpy as np
from PIL import Image
import time

def read_configuration(config_file):
    with open(config_file, 'r') as file:
        config_data = json.load(file)

    num_pixels_x = config_data['Pixels_Eixo_X'] - 1
    num_pixels_y = config_data['Pixels_Eixo_Y'] - 1
    num_images = config_data['Quantidade_Imagens'] - 1
    common_file_name = config_data['Nome_Comum_Arquivos']
    extension = config_data['Extensao_Arquivos']
    primeira_imagem = config_data['Primeira_Imagem']
    ultima_imagem = config_data['Ultima_Imagem']

    # Adicionando zeros à esquerda aos números da primeira e última imagem
    primeira_imagem_str = get_image_number_with_padding(primeira_imagem, 3)  # Sempre preencher 3 zeros à esquerda
    ultima_imagem_str = get_image_number_with_padding(ultima_imagem, 3)      # Sempre preencher 3 zeros à esquerda

    return num_pixels_x, num_pixels_y, num_images, common_file_name, extension, primeira_imagem_str, ultima_imagem_str


def get_image_number_with_padding(image_number, delta_ordem):
    #def get_image_number_with_padding(image_number):
    return str(image_number).zfill(4)


def get_file_name(directory, common_file_name, image_number_str, extension):
    return f"{directory}/{common_file_name}{image_number_str}{extension}"

def pixel_values(directory, num_pixels_x, num_pixels_y, delta_ordem, common_file_name, image_number, extension):
    image_number_str = get_image_number_with_padding(image_number, delta_ordem)
    file_name = get_file_name(directory, common_file_name, image_number_str, extension)

    im = Image.open(file_name)
    C = np.array(im)

    pixel1 = C[0, 0]
    pixel2 = -1
    value2 = value3 = 0

    for j in range(num_pixels_x):
        for k in range(num_pixels_y):
            pixel_value = int(C[k, j])

            if pixel_value != pixel1 and pixel2 == -1:
                pixel2 = pixel_value

            if pixel_value == pixel2:
                value2 += 1
            else:
                value3 += 1

    if value2 > value3 and value3 != 0:
        value2 = 1
        value3 = 0
    else:
        value2 = 0
        value3 = 1

    return pixel1, pixel2, value2, value3

def generate_read_file(config_file):
    inicio = time.time()

    a1 = b1 = c1 = 0
    num_pixels_x, num_pixels_y, num_images, common_file_name, extension, primeira_imagem, ultima_imagem = read_configuration(
        config_file)

    delta_ordem = len(primeira_imagem)

    limit_order = [delta_ordem]
    if delta_ordem > 0:
        for i in range(1, delta_ordem + 1):
            limit_order.append(pow(10, i))
    else:
        limit_order[0] = -1

    with open('Arquivo de Leitura.txt', 'w') as arquivo:
        impresso = str(num_pixels_x * num_pixels_y * num_images) + "\n"
        arquivo.write(impresso)

        C = np.zeros((num_pixels_y, num_pixels_x))
        cont2 = cont3 = cont_prints = 0
        order_count = 0

        for i in range(int(primeira_imagem), int(ultima_imagem) + 1):
            progress = (i - int(primeira_imagem)) / (int(ultima_imagem) - int(primeira_imagem) + 1) * 100
            print(f"Gerando arquivo de leitura: {progress:.2f}%")

            image_number_str = get_image_number_with_padding(i, delta_ordem)
            file_name = get_file_name(directory, common_file_name, image_number_str, extension)

            if i == limit_order[order_count]:
                order_count += 1
                delta_ordem -= 1
                if order_count == len(limit_order):
                    order_count -= 1

            im = Image.open(file_name)
            C[:, :] = np.array(im)

            pixel1, pixel2, value2, value3 = pixel_values(directory, num_pixels_x, num_pixels_y, delta_ordem, common_file_name, i, extension)

            for j in range(num_pixels_x):
                for k in range(num_pixels_y):
                    pixel_value = int(C[k, j])

                    if pixel_value == pixel1:
                        pixel_value = 0
                    elif pixel_value == pixel2:
                        pixel_value = value2
                        cont2 += 1
                    else:
                        pixel_value = value3
                        cont3 += 1

                    impresso = str(pixel_value) + " "
                    cont_prints += 1
                    arquivo.write(impresso)
        print("Gerando arquivo de leitura:  100%")
        
    final = time.time()
    print('Tempo total para gerar arquivo de leitura: ', final - inicio)
    if value2 and cont3 > 0:
        print("\nPorosidade Digital Estimada: ", cont2 / (cont2 + cont3) * 100)
    elif value2 == 0 and cont3 > 0:
        print("\nPorosidade Digital Estimada: ", cont3 / (cont2 + cont3) * 100)
    input("\nAperte Enter para fechar o programa...")

if __name__ == "__main__":
    config_file = 'Configuracao_do_Stack.json'
    directory = 'imgs'  # Altere aqui o diretório onde as imagens estão localizadas
    generate_read_file(config_file)
