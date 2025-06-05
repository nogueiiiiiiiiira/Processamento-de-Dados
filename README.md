# Projeto de Processamento de Dados de Carros

Este projeto consiste em dois programas em C que processam dados de carros. O primeiro programa lê dados de um arquivo CSV e os converte para um arquivo binário. O segundo programa lê o arquivo binário e permite realizar consultas e exibições dos dados através de um menu interativo.

## Requisitos

- Compilador C (gcc ou similar)
- Sistema operacional compatível com C padrão (Windows, Linux, etc.)
- Bibliotecas padrão do C

## Como Compilar

Você pode compilar os programas utilizando o Makefile disponível no projeto, executando o comando:

```
make
```

Ou compilar manualmente com os comandos:

```
gcc -o p1.exe src/p1.c src/lista.c -Iinclude
gcc -o p2.exe src/p2.c src/lista.c src/arvore.c -Iinclude
```

## Como Rodar

### Programa P1

O programa P1 lê um arquivo CSV com dados de carros e gera um arquivo binário.

Uso:

```
./p1.exe <arquivo_entrada.csv> <arquivo_saida.bin>
```

Exemplo:

```
./p1.exe data/carro.csv data/carro.bin
```

### Programa P2

O programa P2 lê o arquivo binário gerado pelo P1 e oferece um menu para realizar consultas nos dados.

Uso:

```
./p2.exe <arquivo_entrada.bin>
```

Exemplo:

```
./p2.exe data/carro.bin
```

## Descrição dos Arquivos

- `data/carro.csv`: Arquivo CSV contendo os dados dos carros (marca, modelo, ano, kilometragem, preço).
- `data/carro.bin`: Arquivo binário gerado pelo programa P1 a partir do CSV.
- `src/p1.c`: Código fonte do programa que converte CSV para binário.
- `src/p2.c`: Código fonte do programa que lê o binário e permite consultas.
- `src/lista.c`: Implementação das listas encadeadas para manipulação dos dados.
- `src/arvore.c`: Implementação das árvores binárias para consultas por kilometragem e preço.
- `include/carro.h`: Definição das estruturas de dados usadas no projeto.

## Funcionalidades

### Programa P1

- Lê dados de carros de um arquivo CSV.
- Armazena os dados em uma lista encadeada.
- Salva os dados em um arquivo binário para uso posterior.

### Programa P2

- Lê os dados do arquivo binário.
- Constrói estruturas de dados para facilitar consultas:
  - Lista encadeada de anos.
  - Árvores binárias para kilometragem e preço.
- Oferece um menu interativo com as seguintes opções:
  1. Exibir todos os carros.
  2. Buscar modelos por substring e ordenar por preço.
  3. Exibir carros com ano maior ou igual a um valor informado.
  4. Buscar carros por intervalo de kilometragem.
  5. Buscar carros por intervalo de preço.
  6. Sair do programa.