#include <stdio.h>
#include <stdlib.h>
#include "../include/carro.h"

// insere um no na arvore binaria de kilometragem
NoArvore* inserir_km(NoArvore* raiz, int km, Carro* carro) {
    if (!raiz) {
        NoArvore* novo = malloc(sizeof(NoArvore));
        novo->chaveInt = km;
        novo->carro = carro;
        novo->esq = novo->dir = NULL;
        return novo;
    }
    if (km < raiz->chaveInt)
        raiz->esq = inserir_km(raiz->esq, km, carro);
    else
        raiz->dir = inserir_km(raiz->dir, km, carro);
    return raiz;
}

// insere um no na arvore binaria de preco
NoArvore* inserir_preco(NoArvore* raiz, float preco, Carro* carro) {
    if (!raiz) {
        NoArvore* novo = malloc(sizeof(NoArvore));
        novo->chaveFloat = preco;
        novo->carro = carro;
        novo->esq = novo->dir = NULL;
        return novo;
    }
    if (preco < raiz->chaveFloat)
        raiz->esq = inserir_preco(raiz->esq, preco, carro);
    else
        raiz->dir = inserir_preco(raiz->dir, preco, carro);
    return raiz;
}

// busca e exibe os carros com kilometragem no intervalo [min, max]
void buscar_km_intervalo(NoArvore* raiz, int min, int max) {
    if (!raiz) return;
    if (raiz->chaveInt >= min)
        buscar_km_intervalo(raiz->esq, min, max);
    if (raiz->chaveInt >= min && raiz->chaveInt <= max)
        printf("%s %s %d %d %.2f\n",
               raiz->carro->marca,
               raiz->carro->modelo,
               raiz->carro->ano,
               raiz->carro->kilometragem,
               raiz->carro->preco);
    if (raiz->chaveInt <= max)
        buscar_km_intervalo(raiz->dir, min, max);
}

// busca e exibe os carros com preco no intervalo [min, max]
void buscar_preco_intervalo(NoArvore* raiz, float min, float max) {
    if (!raiz) return;
    if (raiz->chaveFloat >= min)
        buscar_preco_intervalo(raiz->esq, min, max);
    if (raiz->chaveFloat >= min && raiz->chaveFloat <= max)
        printf("%s %s %d %d %.2f\n",
               raiz->carro->marca,
               raiz->carro->modelo,
               raiz->carro->ano,
               raiz->carro->kilometragem,
               raiz->carro->preco);
    if (raiz->chaveFloat <= max)
        buscar_preco_intervalo(raiz->dir, min, max);
}

// libera a memoria da arvore binaria
void liberar_arvore(NoArvore* raiz) {
    if (!raiz) return;
    liberar_arvore(raiz->esq);
    liberar_arvore(raiz->dir);
    free(raiz);
}
