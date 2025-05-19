# Projeto EDA - Gestão de Antenas e Efeitos Nefastos

## Descrição

Este projeto, desenvolvido para a unidade curricular de Estruturas de Dados Avançadas (EDA), consiste numa aplicação em C para gerir uma rede de antenas, as suas adjacências e efeitos nefastos. Permite criar, remover e pesquisar antenas, gerar e visualizar ligações, realizar travessias em largura (BFS) e profundidade (DFS), e analisar efeitos nefastos na rede.

## Funcionalidades

- **Gestão de Antenas:** Inserção, remoção, pesquisa e listagem de antenas.
- **Adjacências:** Geração e visualização de ligações entre antenas.
- **Efeitos Nefastos:** Identificação e visualização de efeitos nefastos entre antenas.
- **Travessias no Grafo:** Procura em largura (BFS) e profundidade (DFS) a partir de qualquer antena.
- **Persistência:** Leitura e escrita de dados em ficheiros binários.
- **Interface Terminal:** Menus interativos para todas as operações.

## Compilação

Para compilar o projeto, usa o `makefile` fornecido na pasta `src`:

```sh
cd src
make
