#ifndef CARRO_H
#define CARRO_H

#define TAM_MAX_MARCA 21
#define TAM_MAX_MODELO 31

// estrutura principal do carro
typedef struct {
    char marca[TAM_MAX_MARCA];
    char modelo[TAM_MAX_MODELO];
    int ano;
    int kilometragem;
    float preco;
} Carro;

// no da lista encadeada de carros
typedef struct NoDaLista {
    Carro carro;
    struct NoDaLista* proximo;
} NoDaLista;

// no da lista encadeada de anos, cada ano com sua lista de carros
typedef struct NoDoAno {
    int ano;
    NoDaLista* lista_carros_ano;
    struct NoDoAno* proximo;
} NoDoAno;

// no da arvore binaria para kilometragem e preco
typedef struct NoDaArvore {
    int chave_inteira;       // usado para kilometragem
    float chave_decimal;     // usado para preco
    Carro* carro;
    struct NoDaArvore* esquerda;
    struct NoDaArvore* direita;
} NoDaArvore;

// funcoes para manipulacao da lista
NoDaLista* inserir_no_fim_lista(NoDaLista* lista, Carro carro_atual);
void liberar_lista(NoDaLista* lista);

// funcoes para leitura e escrita de arquivos
NoDaLista* carregar_csv(const char* nome_arquivo);
void salvar_binario(const char* nome_arquivo, NoDaLista* lista);
Carro* carregar_binario(const char* nome_arquivo, int* tamanho);

// funcoes para manipulacao da lista de anos
NoDoAno* construir_lista_de_anos(Carro* carros, int tamanho);
void liberar_lista_de_anos(NoDoAno* lista);
void exibir_por_ano(NoDoAno* lista, int ano_minimo);

// funcoes para manipulacao da arvore binaria
NoDaArvore* inserir_por_km(NoDaArvore* raiz, int kilometragem, Carro* carro);
NoDaArvore* inserir_por_preco(NoDaArvore* raiz, float preco, Carro* carro);

// funcoes para busca e exibicao por intervalo
int buscar_por_km_intervalo(NoDaArvore* raiz, int minimo, int maximo);
int buscar_por_preco_intervalo(NoDaArvore* raiz, float minimo, float maximo);
int buscar_por_km_intervalo_wrapper(NoDaArvore* raiz, int minimo, int maximo);
int buscar_por_preco_intervalo_wrapper(NoDaArvore* raiz, float minimo, float maximo);
void liberar_arvore(NoDaArvore* raiz);

// funcoes para busca por substring e exibicao
void buscar_por_modelo(Carro* carros, int tamanho, const char* substring);
void exibir_todos(Carro* carros, int tamanho);
void salvar_csv(const char* nome_arquivo, Carro* carros, int tamanho);

#endif
