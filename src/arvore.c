#include <stdio.h>
#include <stdlib.h>
#include "../include/carro.h"

NoDaArvore* inserir_por_km(NoDaArvore* raiz, int kilometragem, Carro* carro) {
    if (!raiz) {
        NoDaArvore* novo_no = malloc(sizeof(NoDaArvore)); 
        novo_no->chave_inteira = kilometragem; 
        novo_no->carro = carro;
        novo_no->esquerda = novo_no->direita = NULL; 
        return novo_no; 
    }
    if (kilometragem < raiz->chave_inteira) 
        raiz->esquerda = inserir_por_km(raiz->esquerda, kilometragem, carro);
    else 
        raiz->direita = inserir_por_km(raiz->direita, kilometragem, carro);
    return raiz;
}

NoDaArvore* inserir_por_preco(NoDaArvore* raiz, float preco, Carro* carro) {
    if (!raiz) { 
        NoDaArvore* novo_no = malloc(sizeof(NoDaArvore)); 
        novo_no->chave_decimal = preco; 
        novo_no->carro = carro; 
        novo_no->esquerda = novo_no->direita = NULL; // inicializa os ponteiros das subarvores
        return novo_no; 
    }
    if (preco < raiz->chave_decimal) 
        raiz->esquerda = inserir_por_preco(raiz->esquerda, preco, carro);
    else 
        raiz->direita = inserir_por_preco(raiz->direita, preco, carro); 
    return raiz; 
}

static int contar_por_km_intervalo_rec(NoDaArvore* raiz, int minimo, int maximo) {
    if (!raiz) return 0;
    int contador = 0;
    if (raiz->chave_inteira >= minimo) 
        contador += contar_por_km_intervalo_rec(raiz->esquerda, minimo, maximo); 
    if (raiz->chave_inteira >= minimo && raiz->chave_inteira <= maximo) {
        contador++;
    }
    if (raiz->chave_inteira <= maximo)
        contador += contar_por_km_intervalo_rec(raiz->direita, minimo, maximo);
    return contador;
}

static void imprimir_por_km_intervalo_rec(NoDaArvore* raiz, int minimo, int maximo) {
    if (!raiz) return;
    if (raiz->chave_inteira >= minimo)
        imprimir_por_km_intervalo_rec(raiz->esquerda, minimo, maximo); 
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

void liberar_arvore(NoDaArvore* raiz) {
    if (!raiz) return;
    liberar_arvore(raiz->esquerda);
    liberar_arvore(raiz->direita);
    free(raiz);
}
