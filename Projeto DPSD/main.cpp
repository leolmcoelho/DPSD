#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class Config
{
private:
    int width;
    int height;
    int count;
    int size;
    string name;
    int first;
    int last;
    string extension;

public:
    Config()
    {
        width = 0;
        height = 0;
        count = 0;
        size = 0;
        first = 0;
        last = 0;
    }

    void read_config()
    {
        string config_file_path = "Configuracao_do_Stack.txt";

        ifstream config_file(config_file_path);
        if (!config_file)
        {
            cout << "Erro na abertura do arquivo de configuração" << endl;
            return;
        }

        map<string, string> attribute_mappings = {
            {"Quantidade de Pixels da Imagem no Eixo X (largura)", "width"},
            {"Quantidade de Pixels da Imagem no Eixo Y (altura)", "height"},
            {"Quantidade de Imagens", "count"},
            {"Tamanho do Pixel (um)", "size"},
            {"Nome em Comum dos Arquivos de Imagem", "name"},
            {"Número da Primeira Imagem", "first"},
            {"Número da Última Imagem", "last"},
            {"Extensão dos Arquivos de Imagem (.bmp/.tif)", "extension"}};

        string line;
        while (getline(config_file, line))
        {
            size_t pos = line.find(':');
            if (pos != string::npos)
            {
                string key = line.substr(0, pos);
                string value = line.substr(pos + 1);
                key = trim(key);
                value = trim(value);

                if (attribute_mappings.count(key) > 0)
                {
                    string attribute_name = attribute_mappings[key];
                    if (attribute_name == "width")
                    {
                        width = stoi(value);
                    }
                    else if (attribute_name == "height")
                    {
                        height = stoi(value);
                    }
                    else if (attribute_name == "count")
                    {
                        count = stoi(value);
                    }
                    else if (attribute_name == "size")
                    {
                        size = stoi(value);
                    }
                    else if (attribute_name == "name")
                    {
                        name = value;
                    }
                    else if (attribute_name == "first")
                    {
                        first = stoi(value);
                    }
                    else if (attribute_name == "last")
                    {
                        last = stoi(value);
                    }
                    else if (attribute_name == "extension")
                    {
                        extension = value;
                    }
                }
            }
        }

        config_file.close();
    }



    void print_config()
    {
        cout << "Valor de width: " << width << endl;
        cout << "Valor de height: " << height << endl;
        cout << "Valor de count: " << count << endl;
        cout << "Valor de size: " << size << endl;
        cout << "Valor de name: " << name << endl;
        cout << "Valor de first: " << first << endl;
        cout << "Valor de last: " << last << endl;
        cout << "Valor de extension: " << extension << endl;
    }

private:
    string trim(const string &str)
    {
        size_t start = str.find_first_not_of(" \t");
        size_t end = str.find_last_not_of(" \t");
        if (start == string::npos || end == string::npos)
        {
            return "";
        }
        return str.substr(start, end - start + 1);
    }
};

int main()
{
    Config config;

    config.read_config();
    config.print_config();

    return 0;
}

