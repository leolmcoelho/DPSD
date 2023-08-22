# Variáveis de compilação
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++11
LDFLAGS :=

# Nome do executável a ser gerado
TARGET := DPSD

# Lista de arquivos fonte
SRCS := DPSD.cpp LeituraConfiguracao.cpp LeituraArquivo.cpp Filtro.cpp IdentificacaoRaioCritico.cpp AssociacaoPixelRaiosCriticos.cpp TerceiroBloco.cpp SalvarArquivo.cpp

# Lista de arquivos objeto gerados a partir dos arquivos fonte
OBJS := $(SRCS:.cpp=.o)

# Regra principal para a criação do executável
$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

# Regra para a compilação de cada arquivo fonte
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Regra para limpar os arquivos objetos e o executável
clean:
	rm -f $(OBJS) $(TARGET)
