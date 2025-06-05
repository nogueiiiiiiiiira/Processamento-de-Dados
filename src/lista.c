// includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/carro.h"

// insere um carro no final da lista encadeada
NoLista* inserir_fim_lista(NoLista* lista, Carro c) {
    NoLista* novo = malloc(sizeof(NoLista));
    if (!novo) return lista; // malloc failed, return original list
    novo->carro = c;
    novo->prox = NULL;

    if (!lista) {
        return novo;
    }

    NoLista* p = lista;
    while (p->prox) p = p->prox;
    p->prox = novo;
    return lista;
}

// libera a memoria ocupada pela lista encadeada
void liberar_lista(NoLista* lista) {
    while (lista) {
        NoLista* temp = lista;
        lista = lista->prox;
        free(temp);
    }
}

// carrega os dados do arquivo csv para uma lista encadeada
NoLista* carregar_csv(const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "r");
    if (!f) return NULL;

    NoLista* lista = NULL;
    NoLista* fim = NULL; // pointer to last node for efficient insertion
    Carro c;
    while (fscanf(f, "%20[^,],%30[^,],%d,%d,%f\n",
                  c.marca, c.modelo, &c.ano, &c.kilometragem, &c.preco) == 5) {
        NoLista* novo = malloc(sizeof(NoLista));
        if (!novo) {
            liberar_lista(lista);
            fclose(f);
            return NULL;
        }
        novo->carro = c;
        novo->prox = NULL;
        if (!lista) {
            lista = novo;
            fim = novo;
        } else {
            fim->prox = novo;
            fim = novo;
        }
    }

    fclose(f);
    return lista;
}

// salva a lista encadeada em arquivo binario, com a quantidade de registros no inicio
void salvar_binario(const char* nome_arquivo, NoLista* lista) {
    FILE* f = fopen(nome_arquivo, "wb");
    if (!f) return;

    int count = 0;
    NoLista* p = lista;
    while (p) {
        count++;
        p = p->prox;
    }

    fwrite(&count, sizeof(int), 1, f);
    p = lista;
    while (p) {
        fwrite(&p->carro, sizeof(Carro), 1, f);
        p = p->prox;
    }

    fclose(f);
}

// carrega os dados do arquivo binario para um vetor dinamico
Carro* carregar_binario(const char* nome_arquivo, int* tamanho) {
    FILE* f = fopen(nome_arquivo, "rb");
    if (!f) return NULL;

    fread(tamanho, sizeof(int), 1, f);
    Carro* vetor = malloc(sizeof(Carro) * (*tamanho));
    fread(vetor, sizeof(Carro), *tamanho, f);
    fclose(f);
    return vetor;
}

// constroi a lista encadeada de anos unicos, cada ano com sua lista de carros
NoAno* construir_lista_de_ano(Carro* carros, int tamanho) {
    NoAno* lista = NULL;

    for (int i = 0; i < tamanho; i++) {
        int ano = carros[i].ano;
        NoAno* atual = lista;
        NoAno* anterior = NULL;
        while (atual && atual->ano != ano) {
            anterior = atual;
            atual = atual->prox;
        }

        if (!atual) {
            NoAno* novo = malloc(sizeof(NoAno));
            novo->ano = ano;
            novo->carros_ano = NULL;
            novo->prox = NULL;
            if (anterior)
                anterior->prox = novo;
            else
                lista = novo;
            atual = novo;
        }

        Carro c = carros[i];
        atual->carros_ano = inserir_fim_lista(atual->carros_ano, c);
    }

    return lista;
}

// exibe os carros com ano maior ou igual ao ano minimo informado
void exibir_por_ano(NoAno* lista, int ano_minimo) {
    for (NoAno* p = lista; p; p = p->prox) {
        if (p->ano >= ano_minimo) {
            NoLista* q = p->carros_ano;
            while (q) {
                Carro c = q->carro;
                printf("%s %s %d %d %.2f\n", c.marca, c.modelo, c.ano, c.kilometragem, c.preco);
                q = q->prox;
            }
        }
    }
}

// libera a memoria da lista de anos e suas listas de carros
void liberar_lista_de_ano(NoAno* lista) {
    while (lista) {
        liberar_lista(lista->carros_ano);
        NoAno* temp = lista;
        lista = lista->prox;
        free(temp);
    }
}

// funcao de comparacao para ordenar carros por preco
int compara_preco(const void* a, const void* b) {
    Carro* c1 = (Carro*)a;
    Carro* c2 = (Carro*)b;
    if (c1->preco < c2->preco) return -1;
    else if (c1->preco > c2->preco) return 1;
    return 0;
}

// busca carros cujo modelo contenha a substring e exibe ordenado por preco
void buscar_por_modelo(Carro* carros, int tamanho, const char* substring) {
    // First count matches to allocate exact memory
    int count = 0;
    for (int i = 0; i < tamanho; i++) {
        if (strstr(carros[i].modelo, substring)) {
            count++;
        }
    }

    if (count == 0) return;

    Carro* encontrados = malloc(sizeof(Carro) * count);
    if (!encontrados) return;

    int idx = 0;
    for (int i = 0; i < tamanho; i++) {
        if (strstr(carros[i].modelo, substring)) {
            encontrados[idx++] = carros[i];
        }
    }

    qsort(encontrados, count, sizeof(Carro), compara_preco);

    for (int i = 0; i < count; i++) {
        Carro c = encontrados[i];
        printf("%s %s %d %d %.2f\n", c.marca, c.modelo, c.ano, c.kilometragem, c.preco);
    }

    free(encontrados);
}

// exibe todos os carros do vetor
void exibir_todos(Carro* carros, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%s %s %d %d %.2f\n",
            carros[i].marca,
            carros[i].modelo,
            carros[i].ano,
            carros[i].kilometragem,
            carros[i].preco);
    }
}
