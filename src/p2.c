#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/carro.h"

#ifdef _WIN32
#include <windows.h>
#define LIMPAR "cls"
#else
#include <unistd.h>
#define LIMPAR "clear"
#endif

static void limpar_terminal() {
    system(LIMPAR); 
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

static void exibir_menu() {
    limpar_terminal(); 
    printf("\nOpcoes:\n\n");
    printf("1 - Exibir todos os carros\n");
    printf("2 - Buscar modelo por substring e ordenar por preco\n");
    printf("3 - Exibir carros com ano >= informado\n");
    printf("4 - Buscar por kilometragem entre minimo e maximo\n");
    printf("5 - Buscar por preco entre minimo e maximo\n");
    printf("6 - Sair\n");
    printf("\nEscolha: ");
}

int main(int argc, char* argv[]) {
    limpar_terminal(); 
    printf("Programa P2 - Leitura de Arquivo Binario e Operacoes\n\n");
    delay(3); 
    limpar_terminal(); 

    if (argc != 2) {
        fprintf(stderr, "Uso: %s <carro.bin>\n", argv[0]);
        return EXIT_FAILURE; 
    }

    printf("Carregando dados do arquivo binario: %s\n", argv[1]);
    delay(3);
    limpar_terminal();

    int tamanho_vetor;
    Carro* vetor_carros = carregar_binario(argv[1], &tamanho_vetor);
    if (!vetor_carros) {
        fprintf(stderr, "Erro ao carregar binario.\n");
        return EXIT_FAILURE;
    }

    printf("Dados carregados com sucesso. Total de carros: %d\n", tamanho_vetor);
    delay(3);
    limpar_terminal();

    printf("Construindo lista de anos...\n");
    NoDoAno* lista_anos = construir_lista_de_anos(vetor_carros, tamanho_vetor);
    delay(3);
    limpar_terminal();

    printf("Lista de anos construida.\n");
    delay(3);
    limpar_terminal();

    printf("Construindo arvore de kilometragem e preco...\n");
    NoDaArvore* arvore_km = NULL;
    NoDaArvore* arvore_preco = NULL;
    for (int i = 0; i < tamanho_vetor; i++) {
        arvore_km = inserir_por_km(arvore_km, vetor_carros[i].kilometragem, &vetor_carros[i]);
        arvore_preco = inserir_por_preco(arvore_preco, vetor_carros[i].preco, &vetor_carros[i]);
    }

    delay(3);
    limpar_terminal();
    printf("Arvores construidas.\n");
    delay(3);
    limpar_terminal();

    int opcao;
    do {
        exibir_menu();

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida. Por favor, insira um numero.\n");
            while (getchar() != '\n');
            opcao = 0;
            continue;
        }

        getchar();

        switch (opcao) {
            case 1:
                limpar_terminal();
                exibir_todos(vetor_carros, tamanho_vetor);
                salvar_csv("carros_exportados.csv", vetor_carros, tamanho_vetor);
                break;

            case 2: {
                char substring[31];
                printf("\nBuscar por substring do modelo (ex: 'Civic'): ");
                if (fgets(substring, sizeof(substring), stdin) == NULL) {
                    printf("\nErro na leitura da substring.\n");
                    break;
                }

                substring[strcspn(substring, "\n")] = '\0';
                for (int i = 0; substring[i]; i++) {
                    substring[i] = toupper((unsigned char)substring[i]);
                }

                limpar_terminal();
                buscar_por_modelo(vetor_carros, tamanho_vetor, substring);
                printf("\n");
                break;
            }

            case 3: {
                int ano_minimo;
                do {
                    printf("\nAno minimo (ex: 2010): ");
                    if (scanf("%d", &ano_minimo) != 1) {
                        printf("Entrada invalida para ano. Tente novamente.\n\n");
                        while (getchar() != '\n');
                        ano_minimo = -1;
                    } else {
                        while (getchar() != '\n');
                    }
                } while (ano_minimo < 0);

                limpar_terminal();
                exibir_por_ano(lista_anos, ano_minimo);
                printf("\n");
                break;
            }

            case 4: {
                int km_minimo = -1, km_maximo = -1;
                char entrada[50];
                do {
                    printf("\nKilometragem minimo e maximo separados por virgula (ex: 10000, 50000): ");
                    if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
                        printf("Erro na leitura da entrada. Tente novamente.\n");
                        continue;
                    }
                    if (sscanf(entrada, "%d , %d", &km_minimo, &km_maximo) != 2 || km_minimo < 0 || km_maximo < 0 || km_minimo > km_maximo) {
                        printf("Entrada invalida para kilometragem. Tente novamente.\n");
                        km_minimo = -1;
                        km_maximo = -1;
                    }
                } while (km_minimo < 0 || km_maximo < 0);

                limpar_terminal();
                buscar_por_km_intervalo_wrapper(arvore_km, km_minimo, km_maximo);
                printf("\n");
                break;
            }

            case 5: {
                float preco_minimo = -1, preco_maximo = -1;
                char entrada[50];
                do {
                    printf("\nPreco minimo e maximo separados por virgula (ex: 15000.00, 45000.00): ");
                    if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
                        printf("Erro na leitura da entrada. Tente novamente.\n");
                        continue;
                    }
                    if (sscanf(entrada, "%f , %f", &preco_minimo, &preco_maximo) != 2 || preco_minimo < 0 || preco_maximo < 0 || preco_minimo > preco_maximo) {
                        printf("Entrada invalida para preco. Tente novamente.\n");
                        preco_minimo = -1;
                        preco_maximo = -1;
                    }
                } while (preco_minimo < 0 || preco_maximo < 0);

                limpar_terminal();
                buscar_por_preco_intervalo_wrapper(arvore_preco, preco_minimo, preco_maximo);
                printf("\n");
                break;
            }

            case 6:
                limpar_terminal();
                printf("\nPrograma encerrado. Obrigado por usar.\n");
                break;

            default:
                printf("\nOpcao invalida.\n");
                break;
        }

        esperar_enter();

    } while (opcao != 6);

    liberar_lista_de_anos(lista_anos);
    liberar_arvore(arvore_km);
    liberar_arvore(arvore_preco);
    free(vetor_carros);

    return EXIT_SUCCESS;
}
