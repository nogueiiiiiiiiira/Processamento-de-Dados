#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/carro.h"

// insere um carro no final da lista encadeada
NoDaLista* inserir_no_fim_lista(NoDaLista* lista, Carro carro_atual) {
    NoDaLista* novo_no = malloc(sizeof(NoDaLista)); // aloca memoria para o novo no
    if (!novo_no) return lista; // se falhar, retorna a lista original

    novo_no->carro = carro_atual; // copia os dados do carro para o novo no
    novo_no->proximo = NULL; // novo no sera o ultimo, entao aponta para NULL

    if (!lista) return novo_no; // se a lista estava vazia, novo no vira a lista

    NoDaLista* ponteiro = lista; // ponteiro para percorrer a lista
    while (ponteiro->proximo) ponteiro = ponteiro->proximo; // vai ate o ultimo no
    ponteiro->proximo = novo_no; // adiciona o novo no no final
    return lista; // retorna a lista atualizada
}

// libera a memoria ocupada pela lista encadeada
void liberar_lista(NoDaLista* lista) {
    while (lista) {
        NoDaLista* temp = lista; // guarda o no atual
        lista = lista->proximo; // avanca para o proximo no
        free(temp); // libera o no atual
    }
}

// carrega os dados do arquivo csv para uma lista encadeada
NoDaLista* carregar_csv(const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "r"); // abre o arquivo para leitura
    if (!arquivo) return NULL; // retorna NULL se nao conseguir abrir

    NoDaLista* lista = NULL; // ponteiro para o inicio da lista
    NoDaLista* fim = NULL; // ponteiro para o ultimo no da lista
    Carro carro; // variavel temporaria para armazenar dados lidos

    // le cada linha do arquivo e armazena os dados em carro
    while (fscanf(arquivo, "%20[^,],%30[^,],%d,%d,%f\n",
                  carro.marca, carro.modelo, &carro.ano, &carro.kilometragem, &carro.preco) == 5) {

        NoDaLista* novo_no = malloc(sizeof(NoDaLista)); // aloca memoria para novo no
        if (!novo_no) { // se falhar, libera lista e fecha arquivo
            liberar_lista(lista);
            fclose(arquivo);
            return NULL;
        }

        novo_no->carro = carro; // copia os dados para o novo no
        novo_no->proximo = NULL; // novo no sera o ultimo

        if (!lista) { // se lista vazia, novo no vira inicio e fim
            lista = novo_no;
            fim = novo_no;
        } else { // senao, adiciona no final e atualiza fim
            fim->proximo = novo_no;
            fim = novo_no;
        }
    }

    fclose(arquivo); // fecha o arquivo apos leitura
    return lista; // retorna a lista criada
}

// salva a lista encadeada em um arquivo binario
void salvar_binario(const char* nome_arquivo, NoDaLista* lista) {
    FILE* arquivo = fopen(nome_arquivo, "wb"); // abre arquivo para escrita binaria
    if (!arquivo) return; // retorna se nao conseguir abrir

    int contador = 0;
    NoDaLista* ponteiro = lista;
    while (ponteiro) { // conta o numero de carros na lista
        contador++;
        ponteiro = ponteiro->proximo;
    }

    fwrite(&contador, sizeof(int), 1, arquivo); // escreve o numero de carros no arquivo

    ponteiro = lista;
    while (ponteiro) { // escreve os dados de cada carro no arquivo
        fwrite(&ponteiro->carro, sizeof(Carro), 1, arquivo);
        ponteiro = ponteiro->proximo;
    }

    fclose(arquivo); // fecha o arquivo
}

// carrega os dados do arquivo binario para um vetor dinamico
Carro* carregar_binario(const char* nome_arquivo, int* tamanho) {
    FILE* arquivo = fopen(nome_arquivo, "rb"); // abre arquivo para leitura binaria
    if (!arquivo) return NULL; // retorna NULL se nao conseguir abrir

    fread(tamanho, sizeof(int), 1, arquivo); // le o numero de carros
    Carro* vetor = malloc(sizeof(Carro) * (*tamanho)); // aloca vetor para os carros
    fread(vetor, sizeof(Carro), *tamanho, arquivo); // le os dados dos carros

    fclose(arquivo); // fecha o arquivo
    return vetor; // retorna o vetor com os carros
}

// constroi a lista encadeada de anos unicos, com carros em cada ano
NoDoAno* construir_lista_de_anos(Carro* carros, int tamanho) {
    NoDoAno* lista = NULL; // inicio da lista de anos

    for (int i = 0; i < tamanho; i++) {
        int ano_atual = carros[i].ano; // ano do carro atual
        NoDoAno *atual = lista, *anterior = NULL;

        // procura na lista se o ano ja existe
        while (atual && atual->ano != ano_atual) {
            anterior = atual;
            atual = atual->proximo;
        }

        // se nao encontrou o ano, cria um novo no para ele
        if (!atual) {
            NoDoAno* novo_no = malloc(sizeof(NoDoAno));
            novo_no->ano = ano_atual;
            novo_no->lista_carros_ano = NULL;
            novo_no->proximo = NULL;

            if (anterior)
                anterior->proximo = novo_no; // adiciona no final da lista
            else
                lista = novo_no; // se lista vazia, novo no vira inicio

            atual = novo_no;
        }

        // insere o carro na lista de carros do ano correspondente
        atual->lista_carros_ano = inserir_no_fim_lista(atual->lista_carros_ano, carros[i]);
    }

    return lista; // retorna a lista de anos com seus carros
}

// exibe os carros com ano maior ou igual ao ano minimo, formatado em colunas
void exibir_por_ano(NoDoAno* lista, int ano_minimo) {
    int cabecalho_exibido = 0; // flag para imprimir cabecalho uma vez
    int encontrado = 0; // flag para indicar se encontrou algum carro

    for (NoDoAno* p = lista; p; p = p->proximo) {
        if (p->ano >= ano_minimo) { // verifica se o ano atende ao filtro
            if (!cabecalho_exibido) { // imprime cabecalho se ainda nao impresso
                printf("%-20s %-30s %-6s %-12s %s\n", "MARCA", "MODELO", "ANO", "KM", "PRECO");
                printf("--------------------------------------------------------------------------------------\n");
                cabecalho_exibido = 1;
            }

            for (NoDaLista* c = p->lista_carros_ano; c; c = c->proximo) {
                Carro carro = c->carro;
                printf("%-20s %-30s %-6d %-12d R$ %.2f\n", carro.marca, carro.modelo, carro.ano, carro.kilometragem, carro.preco);
                encontrado = 1; // marca que encontrou pelo menos um carro
            }
        }
    }

    if (!encontrado) { // se nao encontrou nenhum carro, imprime mensagem
        printf("Nenhum carro encontrado com ano maior ou igual a %d.\n", ano_minimo);
    }
}

// libera a memoria da lista de anos e suas listas de carros
void liberar_lista_de_anos(NoDoAno* lista) {
    while (lista) {
        liberar_lista(lista->lista_carros_ano); // libera a lista de carros do ano
        NoDoAno* temp = lista; // guarda o no atual
        lista = lista->proximo; // avanca para o proximo no
        free(temp); // libera o no atual
    }
}

// funcao para comparacao de preco (qsort)
int compara_preco(const void* a, const void* b) {
    float preco1 = ((Carro*)a)->preco; // preco do primeiro carro
    float preco2 = ((Carro*)b)->preco; // preco do segundo carro
    return (preco1 > preco2) - (preco1 < preco2); // retorna comparacao para ordenacao crescente
}

// exibe todos os carros formatados em colunas e salva em csv
void exibir_todos(Carro* carros, int tamanho) {
    if (tamanho <= 0) {
        printf("Nenhum carro para exibir.\n"); // mensagem se vetor vazio
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

// salva os carros em formato csv
void salvar_csv(const char* nome_arquivo, Carro* carros, int tamanho) {
    FILE* arquivo = fopen(nome_arquivo, "w"); // abre arquivo para escrita
    if (!arquivo) {
        printf("Erro ao abrir arquivo para salvar CSV.\n"); // mensagem de erro
        return;
    }

    fprintf(arquivo, "MARCA,MODELO,ANO,KM,PRECO\n"); // escreve cabecalho
    for (int i = 0; i < tamanho; i++) {
        fprintf(arquivo, "%s,%s,%d,%d,%.2f\n",
                carros[i].marca, carros[i].modelo,
                carros[i].ano, carros[i].kilometragem,
                carros[i].preco);
    }

    fclose(arquivo); // fecha o arquivo
}

// funcao para buscar carros por substring no modelo, ordenar por preco e exibir
void buscar_por_modelo(Carro* carros, int tamanho, const char* substring) {
    if (tamanho <= 0) {
        printf("Nenhum carro para buscar.\n"); // mensagem se vetor vazio
        return;
    }

    Carro* resultados = malloc(sizeof(Carro) * tamanho); // aloca vetor para resultados
    if (!resultados) {
        printf("Erro de memoria.\n"); // mensagem de erro
        return;
    }

    int contador = 0;
    for (int i = 0; i < tamanho; i++) {
        char modelo_maiusculo[TAM_MAX_MODELO];
        int j;
        for (j = 0; carros[i].modelo[j] && j < TAM_MAX_MODELO - 1; j++) {
            modelo_maiusculo[j] = toupper((unsigned char)carros[i].modelo[j]); // converte para maiusculo
        }
        modelo_maiusculo[j] = '\0';

        if (strstr(modelo_maiusculo, substring)) { // verifica se contem a substring
            resultados[contador++] = carros[i]; // adiciona ao vetor de resultados
        }
    }

    if (contador == 0) { // se nao encontrou nenhum carro
        printf("Nenhum carro encontrado com a substring '%s'.\n", substring);
        free(resultados);
        return;
    }

    qsort(resultados, contador, sizeof(Carro), compara_preco); // ordena resultados por preco

    printf("%-20s %-30s %-6s %-12s %s\n", "MARCA", "MODELO", "ANO", "KM", "PRECO");
    printf("--------------------------------------------------------------------------------------\n");
    for (int i = 0; i < contador; i++) {
        printf("%-20s %-30s %-6d %-12d R$ %.2f\n",
               resultados[i].marca, resultados[i].modelo,
               resultados[i].ano, resultados[i].kilometragem,
               resultados[i].preco);
    }

    free(resultados); // libera o vetor de resultados
}
