#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

// mostra o menu
static void menu() {
    limpar_terminal();
    printf("\nOpcoes:\n\n");
    printf("1 - Exibir todos os carros\n");
    printf("2 - Buscar modelo por substring e ordenar por preco\n");
    printf("3 - Exibir carros com ano >= informado\n");
    printf("4 - Buscar por kilometragem entre min e max\n");
    printf("5 - Buscar por preco entre min e max\n");
    printf("6 - Sair\n");
    printf("\nEscolha: ");
}

// principal funcao p2
int main(int argc, char* argv[]) {
    limpar_terminal();
    printf("Programa P2 - Leitura de arquivo binario e operacoes\n\n");
    delay(3);
    limpar_terminal();

    if (argc != 2) {
        fprintf(stderr, "Uso: %s <carros.bin>\n", argv[0]);
        return EXIT_FAILURE;
    }

    printf("Carregando dados do arquivo binario: %s\n", argv[1]);
    delay(3);
    limpar_terminal();

    int tamanho;
    Carro* carros = carregar_binario(argv[1], &tamanho);

    if (!carros) {
        fprintf(stderr, "Erro ao carregar binario.\n");
        return EXIT_FAILURE;
    }

    printf("Dados carregados com sucesso. Total de carros: %d\n", tamanho);
    delay(3);
    limpar_terminal();

    printf("Construindo lista de anos...\n");
    NoAno* lista_ano = construir_lista_de_ano(carros, tamanho);
    delay(3);
    limpar_terminal();

    printf("Lista de anos construida.\n");
    delay(3);
    limpar_terminal();

    printf("Construindo arvore de kilometragem e preco...\n");
    
    NoArvore* arvore_km = NULL;
    NoArvore* arvore_preco = NULL;

    for (int i = 0; i < tamanho; i++) {
        arvore_km = inserir_km(arvore_km, carros[i].kilometragem, &carros[i]);
        arvore_preco = inserir_preco(arvore_preco, carros[i].preco, &carros[i]);
    }

    delay(3);
    limpar_terminal();
    printf("Arvores construidas.\n");
    delay(3);
    limpar_terminal();

    int opcao;

    do {
        menu();
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida. Por favor, insira um numero.\n");
            while (getchar() != '\n'); // limpar buffer
            opcao = 0;
            continue;
        }
        
        getchar(); 

        switch (opcao) {

            case 1:
                exibir_todos(carros, tamanho);
                break;

            case 2: {
                char substr[31];
                printf("\nSubstring do modelo: ");
                if (fgets(substr, sizeof(substr), stdin) == NULL) {
                    printf("\nErro na leitura da substring.\n");
                    break;
                }

                substr[strcspn(substr, "\n")] = '\0';
                buscar_por_modelo(carros, tamanho, substr);
                break;
            }

            case 3: {
                int ano;
                printf("\nAno minimo: ");
                if (scanf("%d", &ano) != 1) {
                    printf("\nEntrada invalida para ano.\n");
                    while (getchar() != '\n');
                    break;
                }

                exibir_por_ano(lista_ano, ano);
                break;
            }

            case 4: {

                int min, max;
                printf("\nKilometragem min e max: ");
                if (scanf("%d %d", &min, &max) != 2) {
                    printf("\nEntrada invalida para kilometragem.\n");
                    while (getchar() != '\n');
                    break;
                }

                buscar_km_intervalo(arvore_km, min, max);
                break;

            }

            case 5: {
                float min, max;
                printf("\nPreco min e max: ");
                if (scanf("%f %f", &min, &max) != 2) {
                    printf("\nEntrada invalida para preco.\n");
                    while (getchar() != '\n');
                    break;
                }

                buscar_preco_intervalo(arvore_preco, min, max);
                break;
            }

            case 6:
                printf("\nPrograma encerrado. Obrigado por usar.\n");
                break;

            default:
                printf("\nOpcao invalida.\n");
                break;
        }

        esperar_enter();

    } while (opcao != 6);

    liberar_lista_de_ano(lista_ano);
    liberar_arvore(arvore_km);
    liberar_arvore(arvore_preco);
    free(carros);

    return EXIT_SUCCESS;
}
