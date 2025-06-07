# compilador a ser usado
CC = gcc

# opções de compilação: mostrar todos os avisos e otimizar o código
CFLAGS = -Wall -Wextra -O2

# extensão dos arquivos executáveis para Windows
EXT = .exe

# nomes dos executáveis
OUT1 = p1$(EXT)
OUT2 = p2$(EXT)

# alvo padrão: compilar ambos os programas
all: $(OUT1) $(OUT2)

# compila o programa 1 usando p1.c e lista.c
$(OUT1): src/p1.c src/lista.c
	$(CC) $(CFLAGS) -o $(OUT1) src/p1.c src/lista.c

# compila o programa 2 usando p2.c, lista.c e arvore.c
$(OUT2): src/p2.c src/lista.c src/arvore.c
	$(CC) $(CFLAGS) -o $(OUT2) src/p2.c src/lista.c src/arvore.c

# executa ambos os programas, passando arquivos de dados como argumentos
run_both: $(OUT1) $(OUT2)
	./$(OUT1) data/carro.csv data/carro.bin && ./$(OUT2) data/carro.bin

# limpa os executáveis gerados
clean:
	rm -f p1$(EXT) p2$(EXT)
