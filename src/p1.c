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
    system(CLEAR); // executa o comando de limpeza do terminal conforme o sistema operacional
}

// funcao para dar uma pausa para o usuario ler
static void esperar_enter() {
    printf("\nPressione enter para continuar..."); // mensagem para o usuario
    getchar(); // espera o usuario pressionar enter
}

// funcao para delay em segundos
static void delay(double segundos) {
#ifdef _WIN32
    Sleep((DWORD)(segundos * 1000)); // pausa a execucao no windows
#else
    usleep((useconds_t)(segundos * 1000000)); // pausa a execucao em sistemas unix
#endif
}

// funcao principal p1
int main(int argc, char* argv[]) {
    limpar_terminal(); // limpa o terminal no inicio da execucao
    printf("Programa P1 - Leitura de CSV e Gravacao em Arquivo Binario\n\n");
    delay(3); // pausa para o usuario ler
    limpar_terminal(); // limpa o terminal novamente

    if (argc != 3) {
        // verifica se o numero de argumentos esta correto
        fprintf(stderr, "Uso: %s <carro.csv> <carro.bin>\n", argv[0]);
        return EXIT_FAILURE; // encerra com erro se estiver incorreto
    }

    const char* nome_arquivo_csv = argv[1]; // nome do arquivo csv passado por argumento
    const char* nome_arquivo_binario = argv[2]; // nome do arquivo binario passado por argumento

    printf("Abrindo arquivo CSV: %s\n", nome_arquivo_csv);
    delay(3);
    limpar_terminal();

    FILE *arquivo_teste = fopen(nome_arquivo_csv, "r"); // tenta abrir o arquivo csv
    if (!arquivo_teste) {
        // se nao conseguir abrir, imprime erro e encerra
        perror("Erro abrindo arquivo CSV");
        fprintf(stderr, "Erro ao carregar dados de %s\n", nome_arquivo_csv);
        return EXIT_FAILURE;
    }

    fclose(arquivo_teste); // fecha o arquivo de teste de abertura

    printf("Carregando dados do CSV...\n");
    delay(3);
    limpar_terminal();

    NoDaLista* lista_carros = carregar_csv(nome_arquivo_csv); // carrega os dados do csv em uma lista encadeada
    if (!lista_carros) {
        // se houver erro na carga, imprime e encerra
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
    salvar_binario(nome_arquivo_binario, lista_carros); // salva a lista encadeada no arquivo binario

    printf("Dados salvos em %s com sucesso.\n", nome_arquivo_binario);
    delay(3);
    limpar_terminal();

    liberar_lista(lista_carros); // libera a memoria ocupada pela lista
    printf("Memoria liberada.\n");

    esperar_enter(); // espera o usuario pressionar enter antes de encerrar

    return EXIT_SUCCESS; // encerra com sucesso
}
