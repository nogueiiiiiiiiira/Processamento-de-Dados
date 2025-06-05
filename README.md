
# Projeto RA2 - Programação Imperativa (C)

Trabalho de RA2 para a disciplina de Programação Imperativa.

---

## 📌 Objetivo

Este projeto consiste na implementação de dois programas em linguagem C: **P1** e **P2**.  
Eles manipulam dados de veículos contidos em arquivos `.csv` e `.bin`, utilizando estruturas dinâmicas como **listas encadeadas** e **árvores binárias**.

---

## 📂 Estrutura do Projeto

```

trabalho\_ra2/
├── P1/
│   ├── main.c
│   ├── leitura\_csv.c
│   └── ...
├── P2/
│   ├── main.c
│   ├── menu.c
│   ├── estruturas/
│   │   ├── lista\_ano.c/.h
│   │   ├── arvore\_km.c/.h
│   │   ├── arvore\_preco.c/.h
│   └── ...
├── include/
│   ├── carro.h
│   ├── util.h
│   └── ...
├── carros.csv
└── README.md

````

---

## 🧠 Programas

### 🔹 P1 – Leitura e Escrita de Arquivos

- Lê os dados de carros do arquivo `carros.csv`
- Armazena os dados em uma **lista encadeada**
- Salva os dados no arquivo binário `carros.bin`, precedido pelo número total de registros

### 🔹 P2 – Manipulação Avançada de Dados

- Lê `carros.bin` e armazena os dados dinamicamente em um vetor
- Cria:
  - Lista encadeada de anos (`lista_de_ano`)
  - Árvore binária de kilometragens (`arvore_de_kilometragem`)
  - Árvore binária de preços (`arvore_de_preco`)
- Oferece um menu com as seguintes opções:
  1. Exibir todos os registros
  2. Buscar por substring no modelo (ordenado por preço)
  3. Filtrar por ano mínimo
  4. Filtrar por faixa de kilometragem
  5. Filtrar por faixa de preço
  6. Sair

---

## 💡 Como Executar

### 🔧 Compilação (Linux ou WSL)

```bash
gcc -o P1 P1/main.c -Iinclude
gcc -o P2 P2/main.c -Iinclude
````

### ▶️ Execução

```bash
# Executar P1
./P1 carros.csv carros.bin

# Executar P2
./P2 carros.bin
```

---

## 📝 Requisitos Atendidos

* [x] Leitura de CSV e escrita em binário com lista encadeada
* [x] Leitura do binário com alocação dinâmica
* [x] Lista de anos sem repetição
* [x] Árvores binárias para kilometragem e preço
* [x] Filtros e buscas via menu
* [x] Uso de funções e separação em `.h` e `.c`
* [x] Liberação de memória com `free`
* [x] Uso de `argc` e `argv` para parâmetros
* [ ] **Arquivo `carros.csv` com ao menos 30 registros**

---

## ✅ Observações

* Certifique-se de que o `carros.csv` contenha **pelo menos 30 registros**, conforme exigido no enunciado.
* Toda a memória alocada dinamicamente é liberada corretamente no final de cada execução.