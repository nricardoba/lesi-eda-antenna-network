/**
 * @file main.c
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief Ficheiro principal do programa que gere antenas e efeitos nefastos em uma matriz.
 * 
 * repositorio GitHub: https://github.com/ricardobara/TPEDA2425.git
 * 
 * @version 0.1
 * @date 30-03-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "includes.h"

/**
 * @brief Inicializa a lista ligado das antenas, a lista ligada do efeito nefasto e as dimensões da matriz.
 * 
 * Se for possível, executa as funções ExecPreMenu e ExecMainMenu.
 * No final destroi ambas as listas.
 * 
 * @return int 
 */
int main() {
    // inicio da lista ligada das antenas
    Antena* head = NULL;

    // inicio da lista ligada das coordenadas do efeito nefasto
    EfeitoNefasto* inicioNef = NULL;

    // variavel para guardar o numero de linhas e de colunas da matriz, (dimesões da cidade)
    Matriz m;
    m.linhas = 0;
    m.colunas = 0;

    // coordenadas da matriz lidas com sucesso ou
    // matriz lida do ficheiro com sucesso
    if (ExecPreMenu(&head, &inicioNef, &m)) {
        bool term = false;

        // enquanto o utilizador não desejar sair do programa, este continua
        while (!term) {
            
            // enquanto o utilizador não selecionar a opção 'sair', o programa executa a função ExecMainMenu, que vai processar a opção do utilizador
            head = ExecMainMenu(head, &inicioNef, m, &term);
            if (!term) Pausar();
        }
    // coordenadas da matriz invalidas ou
    // não conseguiu ler a matriz do ficheiro ou
    // o utilizador desejou sair
    } else {
        LimpaTerminal();
        printf("Erro a introduzir ou a ler a matriz!\n");
    }

    // mensagem que indica que o programa chegou ao final
    printf("programa terminado!\n\n");

    // destroi a lista ligada das coordenadas do efeito nefasto
    DestroiListaNefasto(&inicioNef);

    // destroi a lista ligada das antenas
    DestroiListaAntenas(&head);
    return 0;
}
