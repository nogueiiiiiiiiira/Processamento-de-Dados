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

static void limpar_terminal() {
    system(CLEAR); 
}

static void esperar_enter() {
    printf("\nPressione enter para continuar..."); 
    getchar(); 
}

static void delay(double segundos) {
#ifdef _WIN32
    Sleep((DWORD)(segundos * 1000)); 
#else
    usleep((useconds_t)(segundos * 1000000)); 
#endif
}

int main(int argc, char* argv[]) {
    limpar_terminal(); 
    printf("Programa P1 - Leitura de CSV e Gravacao em Arquivo Binario\n\n");
    delay(3); 
    limpar_terminal(); 

    if (argc != 3) {
        fprintf(stderr, "Uso: %s <carro.csv> <carro.bin>\n", argv[0]);
        return EXIT_FAILURE; 
    }

    const char* nome_arquivo_csv = argv[1]; 
    const char* nome_arquivo_binario = argv[2]; 

    printf("Abrindo arquivo CSV: %s\n", nome_arquivo_csv);
    delay(3);
    limpar_terminal();

    FILE *arquivo_teste = fopen(nome_arquivo_csv, "r"); 
    if (!arquivo_teste) {
        perror("Erro abrindo arquivo CSV");
        fprintf(stderr, "Erro ao carregar dados de %s\n", nome_arquivo_csv);
        return EXIT_FAILURE;
    }

    fclose(arquivo_teste); 

    printf("Carregando dados do CSV...\n");
    delay(3);
    limpar_terminal();

    NoDaLista* lista_carros = carregar_csv(nome_arquivo_csv); 
    if (!lista_carros) {
        perror("Erro ao carregar dados");
        fprintf(stderr, "Erro ao carregar dados de %s\n", nome_arquivo_csv);
        return EXIT_FAILURE;
    }

    printf("Dados carregados com sucesso.\n");
    delay(3);
    limpar_terminal();

    printf("Salvando dados no arquivo binario: %s\n", nome_arquivo_binario);
    delay(3);
    limpar_terminal();
    salvar_binario(nome_arquivo_binario, lista_carros); 

    printf("Dados salvos em %s com sucesso.\n", nome_arquivo_binario);
    delay(3);
    limpar_terminal();

    liberar_lista(lista_carros); 
    printf("Memoria liberada.\n");

    esperar_enter(); 

    return EXIT_SUCCESS; 
}
