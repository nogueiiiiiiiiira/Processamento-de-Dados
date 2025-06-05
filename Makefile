CC = gcc
CFLAGS = -Wall -Wextra -O2

EXT = .exe
OUT1 = p1$(EXT)
OUT2 = p2$(EXT)

all: $(OUT1) $(OUT2)

$(OUT1): src/p1.c src/lista.c
	$(CC) $(CFLAGS) -o $(OUT1) src/p1.c src/lista.c

$(OUT2): src/p2.c src/lista.c src/arvore.c
	$(CC) $(CFLAGS) -o $(OUT2) src/p2.c src/lista.c src/arvore.c

run_both: $(OUT1) $(OUT2)
	./$(OUT1) data/carro.csv data/carro.bin && ./$(OUT2) data/carro.bin

clean:
	rm -f p1$(EXT) p2$(EXT)
