import tkinter as tk
from tkinter import messagebox, filedialog
import json

class ConfigGUI(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title('Configuração do Stack')
        self.config = Config()

        self.create_widgets()

    def create_widgets(self):
        # Definir os rótulos e caixas de entrada
        fields = [
            ('Diretorio', 'Diretorio'),
            ('Quantidade de Pixels da Imagem no Eixo X (largura)', 'Pixels_Eixo_X'),
            ('Quantidade de Pixels da Imagem no Eixo Y (altura)', 'Pixels_Eixo_Y'),
            ('Quantidade de Imagens', 'Quantidade_Imagens'),
            ('Tamanho do Pixel (um)', 'Tamanho_Pixel'),
            ('Nome em Comum dos Arquivos de Imagem', 'Nome_Comum_Arquivos'),
            ('Número da Primeira Imagem', 'Primeira_Imagem'),
            ('Número da Última Imagem', 'Ultima_Imagem'),
            ('Extensão dos Arquivos de Imagem (.bmp/.tif)', 'Extensao_Arquivos')
        ]

        for i, (label_text, attr_name) in enumerate(fields):
            label = tk.Label(self, text=label_text)
            label.grid(row=i, column=0, sticky=tk.E)

            entry = tk.Entry(self)
            entry.grid(row=i, column=1)
            setattr(self, f"{attr_name}_entry", entry)

        open_button = tk.Button(self, text='Abrir Configuração', command=self.open_config)
        open_button.grid(row=len(fields), column=0)

        save_button = tk.Button(self, text='Salvar Configuração', command=self.save_config)
        save_button.grid(row=len(fields), column=1)

    def open_config(self):
        config_file_path = filedialog.askopenfilename(filetypes=[('JSON Files', '*.json')])
        if not config_file_path:
            return

        try:
            with open(config_file_path, 'r') as config_file:
                config_data = json.load(config_file)

            self.config.update_config(**config_data)
            self.update_entries()
        except Exception as e:
            messagebox.showerror('Erro', f'Erro ao abrir o arquivo de configuração: {e}')

    def save_config(self):
        self.config.update_config(
            Diretorio=self.Diretorio_entry.get(),
            Pixels_Eixo_X=self.Pixels_Eixo_X_entry.get(),
            Pixels_Eixo_Y=self.Pixels_Eixo_Y_entry.get(),
            Quantidade_Imagens=self.Quantidade_Imagens_entry.get(),
            Tamanho_Pixel=self.Tamanho_Pixel_entry.get(),
            Nome_Comum_Arquivos=self.Nome_Comum_Arquivos_entry.get(),
            Primeira_Imagem=self.Primeira_Imagem_entry.get(),
            Ultima_Imagem=self.Ultima_Imagem_entry.get(),
            Extensao_Arquivos=self.Extensao_Arquivos_entry.get()
        )

        config_data = {
            'Diretorio': self.config.Diretorio,
            'Pixels_Eixo_X': self.config.Pixels_Eixo_X,
            'Pixels_Eixo_Y': self.config.Pixels_Eixo_Y,
            'Quantidade_Imagens': self.config.Quantidade_Imagens,
            'Tamanho_Pixel': self.config.Tamanho_Pixel,
            'Nome_Comum_Arquivos': self.config.Nome_Comum_Arquivos,
            'Primeira_Imagem': self.config.Primeira_Imagem,
            'Ultima_Imagem': self.config.Ultima_Imagem,
            'Extensao_Arquivos': self.config.Extensao_Arquivos
        }

        config_file_path = filedialog.asksaveasfilename(filetypes=[('JSON Files', '*.json')])
        if not config_file_path:
            return

        try:
            with open(config_file_path, 'w') as config_file:
                json.dump(config_data, config_file, indent=4)
        except Exception as e:
            messagebox.showerror('Erro', f'Erro ao salvar o arquivo de configuração: {e}')

    def update_entries(self):
        for attr_name in dir(self.config):
            if attr_name.startswith('_'):
                continue

            entry = getattr(self, f"{attr_name}_entry", None)
            if entry is not None:
                entry.delete(0, tk.END)
                entry.insert(tk.END, getattr(self.config, attr_name))


class Config:
    def __init__(self):
        self.Diretorio = None
        self.Pixels_Eixo_X = None
        self.Pixels_Eixo_Y = None
        self.Quantidade_Imagens = None
        self.Tamanho_Pixel = None
        self.Nome_Comum_Arquivos = None
        self.Primeira_Imagem = None
        self.Ultima_Imagem = None
        self.Extensao_Arquivos = None

    def update_config(self, **kwargs):
        for key, value in kwargs.items():
            if hasattr(self, key):
                setattr(self, key, value)


if __name__ == '__main__':
    app = ConfigGUI()
    app.mainloop()
