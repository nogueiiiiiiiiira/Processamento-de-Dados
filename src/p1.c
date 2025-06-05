#include <stdio.h>
#include <stdlib.h>
#include "../include/carro.h"

#ifdef _WIN32
#include <windows.h>
#define CLEAR "cls"
#else
#include <unistd.h>
#define CLEAR "clear"
#endif

// funcao para limpar o terminal
static void limpar_terminal() {
    system(CLEAR);
}

// funcao para dar uma pausa para o usuario ler
static void esperar_enter() {
    printf("\nPressione ENTER para continuar...");
    getchar();
}

// funcao para delay em segundos
static void delay(double seconds) {
#ifdef _WIN32
    Sleep((DWORD)(seconds * 1000));
#else
    usleep((useconds_t)(seconds * 1000000));
#endif
}

// principal funcao p1
int main(int argc, char* argv[]) {
    limpar_terminal();
    printf("Programa P1 - Leitura de CSV e gravacao em arquivo binario\n\n");
    delay(3);
    limpar_terminal();

    if (argc != 3) {
        fprintf(stderr, "Uso: %s <carro.csv> <carro.bin>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* nome_csv = argv[1];
    const char*carro_bin = argv[2];

    printf("Abrindo arquivo CSV: %s\n", nome_csv);
    delay(3);
    limpar_terminal();

    FILE *teste = fopen(nome_csv, "r");
    if (!teste) {
        perror("Erro abrindo arquivo CSV");
        fprintf(stderr, "Erro ao carregar dados de %s\n", nome_csv);
        return EXIT_FAILURE;
    }

    fclose(teste);

    printf("Carregando dados do CSV...\n");
    delay(3);
    limpar_terminal();

    NoLista* lista = carregar_csv(nome_csv);
    if (!lista) {
        perror("Erro ao carregar dados");
        fprintf(stderr, "Erro ao carregar dados de %s\n", nome_csv);
        return EXIT_FAILURE;
    }

    printf("Dados carregados com sucesso.\n");
    delay(3);
    limpar_terminal();

    printf("Salvando dados no arquivo binario: %s\n",carro_bin);
    delay(3);
    limpar_terminal();
    salvar_binario(carro_bin, lista);

    printf("Dados salvos em %s com sucesso.\n",carro_bin);
    delay(3);
    limpar_terminal();

    liberar_lista(lista);
    printf("Memoria liberada.\n");

    esperar_enter();

    return EXIT_SUCCESS;
}
