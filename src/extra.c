/**
 * @file extra.c
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief Ficheiro com funções extra.
 * @version 0.1
 * @date 30-03-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "includes.h"

/**
 * @brief Limpa o terminal.
 * 
 */
void LimpaTerminal() {

    // se o SO for windows
    #ifdef _WIN32

        // limpa o terminal
        system("cls");
    
    // se o SO for mac ou linux
    #else

        // limpa o terminal
        system("clear");
        
    #endif
}

/**
 * @brief Limpa o buffer do teclado.
 * 
 */
void LimpaBuffer() {
    // limpa o buffer do teclado
    while (getchar() != '\n');
}

/**
 * @brief Limpa o buffer do teclado e depois espera que o utilizador precione enter para continuar.
 * 
 */
void Pausar() {
    LimpaBuffer();
    
    // depois de limpar o buffer do teclado apresenta esta mensagem e depois espera que o utilizador precione enter para continuar
    printf("\nENTER para continuar...");
    getchar();
}
