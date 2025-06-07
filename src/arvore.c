#include <stdio.h>
#include <stdlib.h>
#include "../include/carro.h"

// funcao recursiva que insere um novo no na arvore, ordenando pela kilometragem
NoDaArvore* inserir_por_km(NoDaArvore* raiz, int kilometragem, Carro* carro) {
    if (!raiz) {
        NoDaArvore* novo_no = malloc(sizeof(NoDaArvore)); // aloca memoria para o novo no
        novo_no->chave_inteira = kilometragem; // define a chave inteira como a kilometragem
        novo_no->carro = carro; // associa o carro ao no
        novo_no->esquerda = novo_no->direita = NULL; // inicializa os ponteiros das subarvores
        return novo_no; // retorna o novo no criado
    }
    if (kilometragem < raiz->chave_inteira) // se a kilometragem for menor que a chave do no atual
        raiz->esquerda = inserir_por_km(raiz->esquerda, kilometragem, carro); // insere na subarvore esquerda
    else // caso contrario
        raiz->direita = inserir_por_km(raiz->direita, kilometragem, carro); // insere na subarvore direita
    return raiz; // retorna a raiz da arvore
}

// funcao recursiva que insere um novo no na arvore, ordenando pelo preco
NoDaArvore* inserir_por_preco(NoDaArvore* raiz, float preco, Carro* carro) {
    if (!raiz) {  // se a arvore estiver vazia
        NoDaArvore* novo_no = malloc(sizeof(NoDaArvore));  // aloca memoria para o novo no
        novo_no->chave_decimal = preco; // define a chave decimal como o preco
        novo_no->carro = carro; // associa o carro ao no
        novo_no->esquerda = novo_no->direita = NULL; // inicializa os ponteiros das subarvores
        return novo_no; // retorna o novo no criado
    }
    if (preco < raiz->chave_decimal) // se o preco for menor que a chave do no atual
        raiz->esquerda = inserir_por_preco(raiz->esquerda, preco, carro); // insere na subarvore esquerda
    else // caso contrario
        raiz->direita = inserir_por_preco(raiz->direita, preco, carro); // insere na subarvore direita
    return raiz; // retorna a raiz da arvore
}

static int contar_por_km_intervalo_rec(NoDaArvore* raiz, int minimo, int maximo) {
    if (!raiz) return 0;
    int contador = 0;
    if (raiz->chave_inteira >= minimo) // percorre a arvore em ordem, contando os nos cuja kilometragem esta dentro do intervalo
        contador += contar_por_km_intervalo_rec(raiz->esquerda, minimo, maximo); 
    if (raiz->chave_inteira >= minimo && raiz->chave_inteira <= maximo) {
        contador++;
    }
    if (raiz->chave_inteira <= maximo)
        contador += contar_por_km_intervalo_rec(raiz->direita, minimo, maximo);
    return contador; // retorna o total de carros encontrados no intervalo
}

// funcao recursiva para imprimir carros por intervalo de kilometragem
static void imprimir_por_km_intervalo_rec(NoDaArvore* raiz, int minimo, int maximo) {
    if (!raiz) return;
    if (raiz->chave_inteira >= minimo)
        imprimir_por_km_intervalo_rec(raiz->esquerda, minimo, maximo); // percorre a arvore em ordem, imprimindo os carros cuja kilometragem esta dentro do intervalo
    if (raiz->chave_inteira >= minimo && raiz->chave_inteira <= maximo) {
        printf("%-15s\t%-15s\t%-6d\t%-15d\tR$ %-12.2f\n",
               raiz->carro->marca,
               raiz->carro->modelo,
               raiz->carro->ano,
               raiz->carro->kilometragem,
               raiz->carro->preco);
    }
    if (raiz->chave_inteira <= maximo)
        imprimir_por_km_intervalo_rec(raiz->direita, minimo, maximo);
}

// funcao wrapper para buscar carros por intervalo de kilometragem e imprimir cabecalho
int buscar_por_km_intervalo_wrapper(NoDaArvore* raiz, int minimo, int maximo) {
    int total = contar_por_km_intervalo_rec(raiz, minimo, maximo);
    if (total > 0) {
        printf("%-15s %-15s %-6s %-15s %s\n", "MARCA", "MODELO", "ANO", "KM", "PRECO");
        printf("-----------------------------------------------------------------------\n");
        imprimir_por_km_intervalo_rec(raiz, minimo, maximo);
    } else {
        printf("Nenhum carro encontrado no intervalo de kilometragem informado.\n");
    }
    return total;
}

// funcao recursiva para contar carros por intervalo de preco (sem imprimir)
static int contar_por_preco_intervalo_rec(NoDaArvore* raiz, float minimo, float maximo) {
    if (!raiz) return 0;
    int contador = 0;
    if (raiz->chave_decimal >= minimo)
        contador += contar_por_preco_intervalo_rec(raiz->esquerda, minimo, maximo);
    if (raiz->chave_decimal >= minimo && raiz->chave_decimal <= maximo) {
        contador++;
    }
    if (raiz->chave_decimal <= maximo)
        contador += contar_por_preco_intervalo_rec(raiz->direita, minimo, maximo);
    return contador;
}

// funcao recursiva para imprimir carros por intervalo de preco
static void imprimir_por_preco_intervalo_rec(NoDaArvore* raiz, float minimo, float maximo) {
    if (!raiz) return;
    if (raiz->chave_decimal >= minimo)
        imprimir_por_preco_intervalo_rec(raiz->esquerda, minimo, maximo);
    if (raiz->chave_decimal >= minimo && raiz->chave_decimal <= maximo) {
        printf("%-15s\t%-15s\t%-6d\t%-15d\tR$ %-12.2f\n",
               raiz->carro->marca,
               raiz->carro->modelo,
               raiz->carro->ano,
               raiz->carro->kilometragem,
               raiz->carro->preco);
    }
    if (raiz->chave_decimal <= maximo)
        imprimir_por_preco_intervalo_rec(raiz->direita, minimo, maximo);
}

// funcao wrapper para buscar carros por intervalo de preco e imprimir cabecalho
int buscar_por_preco_intervalo_wrapper(NoDaArvore* raiz, float minimo, float maximo) {
    int total = contar_por_preco_intervalo_rec(raiz, minimo, maximo);
    if (total > 0) {
        printf("%-15s %-15s %-6s %-15s %s\n", "MARCA", "MODELO", "ANO", "KM", "PRECO");
        printf("-----------------------------------------------------------------------\n");
        imprimir_por_preco_intervalo_rec(raiz, minimo, maximo);
    } else {
        printf("Nenhum carro encontrado no intervalo de preco informado.\n");
    }
    return total;
}

// funcao recursiva que libera todos os nos da arvore em pos-ordem
void liberar_arvore(NoDaArvore* raiz) {
    if (!raiz) return;
    liberar_arvore(raiz->esquerda);
    liberar_arvore(raiz->direita);
    free(raiz);
}
