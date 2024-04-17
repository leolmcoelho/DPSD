import tkinter as tk
from tkinter import messagebox, filedialog


class ConfigGUI(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title('Configuração do Stack')
        self.config = Config()

        self.create_widgets()

    def create_widgets(self):
        width_label = tk.Label(self, text='Quantidade de Pixels da Imagem no Eixo X (largura):')
        width_entry = tk.Entry(self)
        height_label = tk.Label(self, text='Quantidade de Pixels da Imagem no Eixo Y (altura):')
        height_entry = tk.Entry(self)
        count_label = tk.Label(self, text='Quantidade de Imagens:')
        count_entry = tk.Entry(self)
        size_label = tk.Label(self, text='Tamanho do Pixel (um):')
        size_entry = tk.Entry(self)
        name_label = tk.Label(self, text='Nome em Comum dos Arquivos de Imagem:')
        name_entry = tk.Entry(self)
        first_label = tk.Label(self, text='Número da Primeira Imagem:')
        first_entry = tk.Entry(self)
        last_label = tk.Label(self, text='Número da Última Imagem:')
        last_entry = tk.Entry(self)
        extension_label = tk.Label(self, text='Extensão dos Arquivos de Imagem (.bmp/.tif):')
        extension_entry = tk.Entry(self)
        open_button = tk.Button(self, text='Abrir Configuração', command=self.open_config)
        save_button = tk.Button(self, text='Salvar Configuração', command=self.save_config)

        width_label.grid(row=0, column=0, sticky=tk.E)
        width_entry.grid(row=0, column=1)
        height_label.grid(row=1, column=0, sticky=tk.E)
        height_entry.grid(row=1, column=1)
        count_label.grid(row=2, column=0, sticky=tk.E)
        count_entry.grid(row=2, column=1)
        size_label.grid(row=3, column=0, sticky=tk.E)
        size_entry.grid(row=3, column=1)
        name_label.grid(row=4, column=0, sticky=tk.E)
        name_entry.grid(row=4, column=1)
        first_label.grid(row=5, column=0, sticky=tk.E)
        first_entry.grid(row=5, column=1)
        last_label.grid(row=6, column=0, sticky=tk.E)
        last_entry.grid(row=6, column=1)
        extension_label.grid(row=7, column=0, sticky=tk.E)
        extension_entry.grid(row=7, column=1)
        open_button.grid(row=8, column=0)
        save_button.grid(row=8, column=1)

        # Store the entry fields as instance attributes
        self.width_entry = width_entry
        self.height_entry = height_entry
        self.count_entry = count_entry
        self.size_entry = size_entry
        self.name_entry = name_entry
        self.first_entry = first_entry
        self.last_entry = last_entry
        self.extension_entry = extension_entry

    def open_config(self):
        self.config.read_config()
        self.update_entries()

    def save_config(self):
        self.config.update_config(
            width=self.width_entry.get(),
            height=self.height_entry.get(),
            count=self.count_entry.get(),
            size=self.size_entry.get(),
            name=self.name_entry.get(),
            first=self.first_entry.get(),
            last=self.last_entry.get(),
            extension=self.extension_entry.get()
        )
        self.config.save_config()

    def update_entries(self):
        config = self.config
        if config.width is not None:
            self.width_entry.delete(0, tk.END)
            self.width_entry.insert(tk.END, config.width)
        if config.height is not None:
            self.height_entry.delete(0, tk.END)
            self.height_entry.insert(tk.END, config.height)
        if config.count is not None:
            self.count_entry.delete(0, tk.END)
            self.count_entry.insert(tk.END, config.count)
        if config.size is not None:
            self.size_entry.delete(0, tk.END)
            self.size_entry.insert(tk.END, config.size)
        if config.name is not None:
            self.name_entry.delete(0, tk.END)
            self.name_entry.insert(tk.END, config.name)
        if config.first is not None:
            self.first_entry.delete(0, tk.END)
            self.first_entry.insert(tk.END, config.first)
        if config.last is not None:
            self.last_entry.delete(0, tk.END)
            self.last_entry.insert(tk.END, config.last)
        if config.extension is not None:
            self.extension_entry.delete(0, tk.END)
            self.extension_entry.insert(tk.END, config.extension)


class Config:
    def __init__(self):
        self.width = None
        self.height = None
        self.count = None
        self.size = None
        self.name = None
        self.first = None
        self.last = None
        self.extension = None


    def read_config(self):
        config_file_path = filedialog.askopenfilename(filetypes=[('Text Files', '*.txt')])
        if not config_file_path:
            return

        with open(config_file_path, 'r') as config_file:
            lines = config_file.readlines()

        attribute_mappings = {
            'Quantidade de Pixels da Imagem no Eixo X (largura)': 'width',
            'Quantidade de Pixels da Imagem no Eixo Y (altura)': 'height',
            'Quantidade de Imagens': 'count',
            'Tamanho do Pixel (um)': 'size',
            'Nome em Comum dos Arquivos de Imagem': 'name',
            'Número da Primeira Imagem': 'first',
            'Número da Última Imagem': 'last',
            'Extensão dos Arquivos de Imagem (.bmp/.tif)': 'extension'
        }

        for line in lines:
            parts = line.split(':')
            if len(parts) == 2:
                key = parts[0].strip()
                value = parts[1].strip()
                value = value.replace(' ', '')  # Remover espaços extras

                if key in attribute_mappings:
                    attribute_name = attribute_mappings[key]
                    if hasattr(self, attribute_name):
                        attribute_value = getattr(self, attribute_name)
                        if value.isdigit():
                            value = int(value)
                        setattr(self, attribute_name, value)
                        
                        


    def show_config_error(self, field, value):
        messagebox.showerror('Erro', f'O valor "{value}" do campo "{field}" não é um número válido.')
        self.reset_config()
        return


    def save_config(self):
        config_file_path = filedialog.asksaveasfilename(filetypes=[('Text Files', '*.txt')])
        if not config_file_path:
            return

        with open(config_file_path, 'w') as config_file:
            config_file.write(f'Quantidade de Pixels da Imagem no Eixo X (largura): {self.width}\n')
            config_file.write(f'Quantidade de Pixels da Imagem no Eixo Y (altura): {self.height}\n')
            config_file.write(f'Quantidade de Imagens: {self.count}\n')
            config_file.write(f'Tamanho do Pixel (um): {self.size}\n')
            config_file.write(f'Nome em Comum dos Arquivos de Imagem: {self.name}\n')
            config_file.write(f'Número da Primeira Imagem: {self.first}\n')
            config_file.write(f'Número da Última Imagem: {self.last}\n')
            config_file.write(f'Extensão dos Arquivos de Imagem (.bmp/.tif): {self.extension}\n')

    def update_config(
            self, width=None, height=None, count=None, size=None, name=None, first=None, last=None,
            extension=None):
        if width is not None:
            self.width = width
        if height is not None:
            self.height = height
        if count is not None:
            self.count = count
        if size is not None:
            self.size = size
        if name is not None:
            self.name = name
        if first is not None:
            self.first = first
        if last is not None:
            self.last = last
        if extension is not None:
            self.extension = extension

    def reset_config(self):
        self.width = None
        self.height = None
        self.count = None
        self.size = None
        self.name = None
        self.first = None
        self.last = None
        self.extension = None


if __name__ == '__main__':
    app = ConfigGUI()
    app.mainloop()
    # config = Config()
    # config.read_config()
    #
    # print(config.width)
    # print(config.height)
    # print(config.count)
    # print(config.size)
    # print(config.name)
    # print(config.first)
    # print(config.last)
    # print(config.extension)
