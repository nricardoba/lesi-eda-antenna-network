/**
 * @file menus.c
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief Ficheiro que gere as funções sobre os menus do projeto.
 * @version 0.1
 * @date 30-03-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "includes.h"

int PreMenu() {
    int op;
    bool term = false;

    while (!term) {
        LimpaTerminal();
        printf("Escolha uma opção:\n\n");

        printf("1 - Criar nova Matriz\n");
        printf("2 - Carregar Matriz do ficheiro\n");
        printf("0 - Sair\n\n");

        printf("opção: ");
        scanf("%d", &op);
        printf("\n");

        if (op >= 0 && op <= 2) term = true;
        else {
            printf("opção invalida!\n");
            Pausar();
        }
    }

    return op;
}

int MainMenu() {
    int op;
    bool term = false;

    while (!term) {
        LimpaTerminal();
        printf("Escolha uma opção:\n\n");

        printf("1 - Adicionar antena\n");
        printf("2 - Alterar antena\n");
        printf("3 - Remover antena\n\n");

        printf("4 - Mostrar matriz com efeito nefasto\n");
        printf("5 - Mostrar matriz sem efeito nefasto\n\n");

        printf("6 - Mostra lista das Antenas\n");
        printf("7 - Mostra lista do Efeito Nefasto\n\n");
        
        printf("8 - Guardar a matriz em ficheiro\n");
        printf("\n0 - Sair\n\n");

        printf("opção: ");
        scanf("%d", &op);
        printf("\n");

        if (op >= 0 && op <= 8) term = true;
        else {
            printf("opção invalida!\n");
            Pausar();
        }
    }

    return op;
}
