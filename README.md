# 📊 Projeto de Processamento de Dados de Carros

Este projeto em C tem como objetivo processar e consultar dados de carros a partir de um arquivo CSV. Ele é composto por dois programas:

- **P1**: Converte os dados de um arquivo CSV em um arquivo binário.
- **P2**: Lê o arquivo binário e permite consultas interativas utilizando estruturas de dados como listas e árvores binárias.

---

## 🗂 Estrutura do Projeto

```

Processamento-de-Dados/
├── data/
│   ├── carro.csv              # Arquivo de entrada com os dados dos carros
│   ├── carro.bin              # Arquivo binário gerado pelo programa P1
│   └── carros\_exportados.csv  # Resultados exportados da opção 2 do P2
│
├── include/
│   └── carro.h                # Definições das estruturas de dados
│
├── src/
│   ├── p1.c                   # Lê CSV e gera arquivo binário
│   ├── p2.c                   # Menu interativo para consulta de dados
│   ├── lista.c                # Implementação das listas encadeadas
│   └── arvore.c               # Implementação das árvores binárias
│
├── .vscode/                   # Configurações para editores de código
├── Makefile                   # Automatiza a compilação dos programas
└── README.md                  # Documentação do projeto

````

---

## ⚙️ Requisitos

- Compilador C (ex: `gcc`)
- Sistema operacional com suporte a C padrão (Linux, Windows, etc.)
- Terminal/Shell para executar os programas

---

## 🛠 Como Compilar

Você pode usar o `Makefile` para compilar tudo de forma simples:

```bash
make
````

Ou, se preferir, compile manualmente:

```bash
gcc -o p1.exe src/p1.c src/lista.c -Iinclude
gcc -o p2.exe src/p2.c src/lista.c src/arvore.c -Iinclude
```

---

## 🚀 Como Executar

### 1. Gerar o Arquivo Binário

Use o programa `p1.exe` para converter o arquivo CSV em binário:

```bash
./p1.exe data/carro.csv data/carro.bin
```

**Saída esperada:** será criado o arquivo `data/carro.bin`.

---

### 2. Realizar Consultas

Use o programa `p2.exe` para acessar um menu de consultas:

```bash
./p2.exe data/carro.bin
```

---

## 🔎 Funcionalidades do Menu Interativo (P2)

1. **Exibir todos os carros**
2. **Buscar modelos por substring** (ordenação por preço)
3. **Filtrar por ano** (maior ou igual ao informado)
4. **Buscar por intervalo de kilometragem**
5. **Buscar por intervalo de preço**
6. **Sair do programa**

---

## 📁 Detalhes dos Arquivos

* `carro.csv`: Arquivo com colunas como marca, modelo, ano, kilometragem, preço.
* `carro.bin`: Arquivo binário gerado por P1 e usado como entrada em P2.
* `carros_exportados.csv`: Resultados exportados automaticamente ao usar a opção 2 do P2.
* `p1.c`: Constrói a estrutura de dados e gera `carro.bin`.
* `p2.c`: Permite navegação e buscas nos dados.
* `lista.c`: Implementa listas encadeadas.
* `arvore.c`: Implementa árvores binárias para consultas eficientes.
* `carro.h`: Define a estrutura dos dados e funções auxiliares.

---

## 📤 Exportação de Resultados

Durante a execução do menu do Programa P2 (busca por modelo com ordenação por preço), os resultados também são exportados automaticamente para:

```
data/carros_exportados.csv
```

Esse arquivo CSV contém os modelos encontrados, permitindo reutilização ou análise externa dos dados.
