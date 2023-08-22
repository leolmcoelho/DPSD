package main

import (
	"encoding/json"
	"fmt"
	"image"
	"image/color"
	"image/png"
	"io/ioutil"
	"strconv"

	/*"image/jpeg"*/
	"os"
)

type Configuration struct {
	PixelsEixoX       int    `json:"Pixels_Eixo_X"`
	PixelsEixoY       int    `json:"Pixels_Eixo_Y"`
	QuantidadeImagens int    `json:"Quantidade_Imagens"`
	NomeComumArquivos string `json:"Nome_Comum_Arquivos"`
	ExtensaoArquivos  string `json:"Extensao_Arquivos"`
	PrimeiraImagem    int    `json:"Primeira_Imagem"`
	UltimaImagem      int    `json:"Ultima_Imagem"`
}

func readConfiguration(configFile string) (int, int, int, string, string, string, string, error) {
	fileContent, err := ioutil.ReadFile(configFile)
	if err != nil {
		return 0, 0, 0, "", "", "", "", err
	}

	var configData Configuration
	err = json.Unmarshal(fileContent, &configData)
	if err != nil {
		return 0, 0, 0, "", "", "", "", err
	}

	numPixelsX := configData.PixelsEixoX - 1
	numPixelsY := configData.PixelsEixoY - 1
	numImages := configData.QuantidadeImagens - 1
	commonFileName := configData.NomeComumArquivos
	extension := configData.ExtensaoArquivos
	primeiraImagemStr := getImageNumberWithPadding(configData.PrimeiraImagem, 3)
	ultimaImagemStr := getImageNumberWithPadding(configData.UltimaImagem, 3)

	return numPixelsX, numPixelsY, numImages, commonFileName, extension, primeiraImagemStr, ultimaImagemStr, nil
}

func getImageNumberWithPadding(number, padding int) string {
	return fmt.Sprintf("%0" + strconv.Itoa(padding) + "d", number)
}

func getFileName(directory, commonFileName, imageNumberStr, extension string) string {
	return fmt.Sprintf("%s/%s%s%s", directory, commonFileName, imageNumberStr, extension)
}

func pixelValues(directory string, numPixelsX, numPixelsY, deltaOrdem int, commonFileName, extension string, imageNumber int) (int, int, int, int) {
	imageNumberStr := getImageNumberWithPadding(imageNumber, deltaOrdem)
	fileName := getFileName(directory, commonFileName, imageNumberStr, extension)

	file, err := os.Open(fileName)
	if err != nil {
		panic(err)
	}
	defer file.Close()

	var im image.Image
	if extension == ".jpg" || extension == ".jpeg" {
		im, _, err = image.Decode(file)
		if err != nil {
			panic(err)
		}
	} else if extension == ".png" {
		im, err = png.Decode(file)
		if err != nil {
			panic(err)
		}
	} else {
		panic("Unsupported file extension")
	}

	bounds := im.Bounds()
	width := bounds.Dx()
	height := bounds.Dy()

	pixel1 := im.At(0, 0)
	var pixel2 color.Color
	value2 := 0
	value3 := 0

	for j := 0; j < width; j++ {
		for k := 0; k < height; k++ {
			r, g, b, _ := im.At(j, k).RGBA()
			pixelValue := color.RGBA{uint8(r >> 8), uint8(g >> 8), uint8(b >> 8), 0}

			if pixelValue != pixel1 && pixel2 == (color.RGBA{}) {
				pixel2 = pixelValue
			}

			if pixelValue == pixel2 {
				value2++
			} else {
				value3++
			}
		}
	}

	if value2 > value3 && value3 != 0 {
		value2 = 1
		value3 = 0
	} else {
		value2 = 0
		value3 = 1
	}

	return pixel1, pixel2, value2, value3
}

func main() {
	numPixelsX, numPixelsY, numImages, commonFileName, extension, primeiraImagemStr, ultimaImagemStr, err := readConfiguration("config.json")
	if err != nil {
		fmt.Println("Error:", err)
		return
	}

	fmt.Println("Num Pixels X:", numPixelsX)
	fmt.Println("Num Pixels Y:", numPixelsY)
	fmt.Println("Num Images:", numImages)
	fmt.Println("Common File Name:", commonFileName)
	fmt.Println("Extension:", extension)
	fmt.Println("Primeira Imagem:", primeiraImagemStr)
	fmt.Println("Ultima Imagem:", ultimaImagemStr)


	pixel1, pixel2, value2, value3 := pixelValues(directory, numPixelsX, numPixelsY, deltaOrdem, commonFileName, extension, imageNumber)
	fmt.Println("Pixel 1:", pixel1)
	fmt.Println("Pixel 2:", pixel2)
	fmt.Println("Value 2:", value2)
	fmt.Println("Value 3:", value3)
}
