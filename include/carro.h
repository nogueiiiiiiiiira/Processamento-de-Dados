#ifndef CARRO_H
#define CARRO_H

#define MAX_MARCA 21
#define MAX_MODELO 31

// estrutura principal de carro
typedef struct {
    char marca[MAX_MARCA];
    char modelo[MAX_MODELO];
    int ano;
    int kilometragem;
    float preco;
} Carro;

// lista encadeada de carros
typedef struct NoLista {
    Carro carro;
    struct NoLista* prox;
} NoLista;

// lista encadeada de anos
typedef struct NoAno {
    int ano;
    NoLista* carros_ano;
    struct NoAno* prox;
} NoAno;

// nó de árvore binária usado para kilometragem e preço
typedef struct NoArvore {
    int chaveInt;       // usado para kilometragem
    float chaveFloat;   // usado para preço
    Carro* carro;
    struct NoArvore* esq;
    struct NoArvore* dir;
} NoArvore;

// funções de manipulação de lista
NoLista* inserir_fim_lista(NoLista* lista, Carro c);
void liberar_lista(NoLista* lista);

// leitura e escrita de arquivos
NoLista* carregar_csv(const char* nome_arquivo);
void salvar_binario(const char* nome_arquivo, NoLista* lista);
Carro* carregar_binario(const char* nome_arquivo, int* tamanho);

// manipulação de lista_de_ano
NoAno* construir_lista_de_ano(Carro* carros, int tamanho);
void liberar_lista_de_ano(NoAno* lista);
void exibir_por_ano(NoAno* lista, int ano_minimo);

// manipulação de árvores
NoArvore* inserir_km(NoArvore* raiz, int km, Carro* carro); 
NoArvore* inserir_preco(NoArvore* raiz, float preco, Carro* carro); 

void buscar_km_intervalo(NoArvore* raiz, int min, int max); 
void buscar_preco_intervalo(NoArvore* raiz, float min, float max); 
void liberar_arvore(NoArvore* raiz);

// busca por substring e ordenação
void buscar_por_modelo(Carro* carros, int tamanho, const char* substring);
void exibir_todos(Carro* carros, int tamanho);

#endif
