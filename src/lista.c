#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/carro.h"

NoDaLista* inserir_no_fim_lista(NoDaLista* lista, Carro carro_atual) {
    NoDaLista* novo_no = malloc(sizeof(NoDaLista)); 
    if (!novo_no) return lista; 

    novo_no->carro = carro_atual; 
    novo_no->proximo = NULL; 

    if (!lista) return novo_no; 

    NoDaLista* ponteiro = lista; 
    while (ponteiro->proximo) ponteiro = ponteiro->proximo; 
    ponteiro->proximo = novo_no; 
    return lista; 
}

void liberar_lista(NoDaLista* lista) {
    while (lista) {
        NoDaLista* temp = lista; 
        lista = lista->proximo; 
        free(temp); 
    }
}

NoDaLista* carregar_csv(const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "r"); 
    if (!arquivo) return NULL; 
    NoDaLista* lista = NULL;
    NoDaLista* fim = NULL; 
    Carro carro; 

    while (fscanf(arquivo, "%20[^,],%30[^,],%d,%d,%f\n",
                  carro.marca, carro.modelo, &carro.ano, &carro.kilometragem, &carro.preco) == 5) {

        NoDaLista* novo_no = malloc(sizeof(NoDaLista)); 
        if (!novo_no) { 
            liberar_lista(lista);
            fclose(arquivo);
            return NULL;
        }

        novo_no->carro = carro; 
        novo_no->proximo = NULL; 

        if (!lista) { 
            lista = novo_no;
            fim = novo_no;
        } else { 
            fim->proximo = novo_no;
            fim = novo_no;
        }
    }

    fclose(arquivo);
    return lista; 
}

void salvar_binario(const char* nome_arquivo, NoDaLista* lista) {
    FILE* arquivo = fopen(nome_arquivo, "wb"); 
    if (!arquivo) return; 

    int contador = 0;
    NoDaLista* ponteiro = lista;
    while (ponteiro) { 
        contador++;
        ponteiro = ponteiro->proximo;
    }

    fwrite(&contador, sizeof(int), 1, arquivo); 

    ponteiro = lista;
    while (ponteiro) { 
        fwrite(&ponteiro->carro, sizeof(Carro), 1, arquivo);
        ponteiro = ponteiro->proximo;
    }

    fclose(arquivo); 
}

Carro* carregar_binario(const char* nome_arquivo, int* tamanho) {
    FILE* arquivo = fopen(nome_arquivo, "rb"); 
    if (!arquivo) return NULL; 

    fread(tamanho, sizeof(int), 1, arquivo); 
    Carro* vetor = malloc(sizeof(Carro) * (*tamanho)); 
    fread(vetor, sizeof(Carro), *tamanho, arquivo); 

    fclose(arquivo); 
    return vetor; 
}

NoDoAno* construir_lista_de_anos(Carro* carros, int tamanho) {
    NoDoAno* lista = NULL; 

    for (int i = 0; i < tamanho; i++) {
        int ano_atual = carros[i].ano; 
        NoDoAno *atual = lista, *anterior = NULL;

        while (atual && atual->ano != ano_atual) {
            anterior = atual;
            atual = atual->proximo;
        }

        if (!atual) {
            NoDoAno* novo_no = malloc(sizeof(NoDoAno));
            novo_no->ano = ano_atual;
            novo_no->lista_carros_ano = NULL;
            novo_no->proximo = NULL;

            if (anterior)
                anterior->proximo = novo_no; 
            else
                lista = novo_no; 

            atual = novo_no;
        }

        atual->lista_carros_ano = inserir_no_fim_lista(atual->lista_carros_ano, carros[i]);
    }

    return lista; 
}

void exibir_por_ano(NoDoAno* lista, int ano_minimo) {
    int cabecalho_exibido = 0; 
    int encontrado = 0; 

    for (NoDoAno* p = lista; p; p = p->proximo) {
        if (p->ano >= ano_minimo) { 
            if (!cabecalho_exibido) { 
                printf("%-20s %-30s %-6s %-12s %s\n", "MARCA", "MODELO", "ANO", "KM", "PRECO");
                printf("--------------------------------------------------------------------------------------\n");
                cabecalho_exibido = 1;
            }

            for (NoDaLista* c = p->lista_carros_ano; c; c = c->proximo) {
                Carro carro = c->carro;
                printf("%-20s %-30s %-6d %-12d R$ %.2f\n", carro.marca, carro.modelo, carro.ano, carro.kilometragem, carro.preco);
                encontrado = 1; 
            }
        }
    }

    if (!encontrado) { 
        printf("Nenhum carro encontrado com ano maior ou igual a %d.\n", ano_minimo);
    }
}

void liberar_lista_de_anos(NoDoAno* lista) {
    while (lista) {
        liberar_lista(lista->lista_carros_ano); 
        NoDoAno* temp = lista; 
        lista = lista->proximo; 
        free(temp); 
    }
}

int compara_preco(const void* a, const void* b) {
    float preco1 = ((Carro*)a)->preco; 
    float preco2 = ((Carro*)b)->preco; 
    return (preco1 > preco2) - (preco1 < preco2); 
}

void exibir_todos(Carro* carros, int tamanho) {
    if (tamanho <= 0) {
        printf("Nenhum carro para exibir.\n"); 
        return;
    }

    printf("%-20s %-30s %-6s %-12s %s\n", "MARCA", "MODELO", "ANO", "KM", "PRECO");
    printf("--------------------------------------------------------------------------------------\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%-20s %-30s %-6d %-12d R$ %.2f\n",
               carros[i].marca, carros[i].modelo,
               carros[i].ano, carros[i].kilometragem,
               carros[i].preco);
    }
}

void salvar_csv(const char* nome_arquivo, Carro* carros, int tamanho) {
    FILE* arquivo = fopen(nome_arquivo, "w"); 
    if (!arquivo) {
        printf("Erro ao abrir arquivo para salvar CSV.\n"); 
        return;
    }

    fprintf(arquivo, "MARCA,MODELO,ANO,KM,PRECO\n"); 
    for (int i = 0; i < tamanho; i++) {
        fprintf(arquivo, "%s,%s,%d,%d,%.2f\n",
                carros[i].marca, carros[i].modelo,
                carros[i].ano, carros[i].kilometragem,
                carros[i].preco);
    }

    fclose(arquivo); 
}

void buscar_por_modelo(Carro* carros, int tamanho, const char* substring) {
    if (tamanho <= 0) {
        printf("Nenhum carro para buscar.\n"); 
        return;
    }

    Carro* resultados = malloc(sizeof(Carro) * tamanho); 
    if (!resultados) {
        printf("Erro de memoria.\n"); 
        return;
    }

    int contador = 0;
    for (int i = 0; i < tamanho; i++) {
        char modelo_maiusculo[TAM_MAX_MODELO];
        int j;
        for (j = 0; carros[i].modelo[j] && j < TAM_MAX_MODELO - 1; j++) {
            modelo_maiusculo[j] = toupper((unsigned char)carros[i].modelo[j]); 
        }
        modelo_maiusculo[j] = '\0';

        if (strstr(modelo_maiusculo, substring)) { 
            resultados[contador++] = carros[i]; 
        }
    }

    if (contador == 0) { 
        printf("Nenhum carro encontrado com a substring '%s'.\n", substring);
        free(resultados);
        return;
    }

    qsort(resultados, contador, sizeof(Carro), compara_preco); 

    printf("%-20s %-30s %-6s %-12s %s\n", "MARCA", "MODELO", "ANO", "KM", "PRECO");
    printf("--------------------------------------------------------------------------------------\n");
    for (int i = 0; i < contador; i++) {
    printf("%-20s %-30s %-6d %-12d R$ %.2f\n",
           resultados[i].marca, resultados[i].modelo,
           resultados[i].ano, resultados[i].kilometragem,
           resultados[i].preco);
    }

    free(resultados); 
}
