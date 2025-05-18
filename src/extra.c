/**
 * @file extra.c
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief Ficheiro com as funções extra do projeto.
 * @version 0.1
 * @date 18-05-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "includes.h"

/**
 * @brief Função auxiliar que limpa o terminal.
 * 
 */
void LimpaTerminal() {

    #ifdef _WIN32           // windows
        system("cls");
    
    #else                   // mac ou linux
        system("clear");
        
    #endif
}

/**
 * @brief Função auxiliar que limpa o buffer do teclado.
 * 
 */
void LimpaBuffer() {
    // limpa o buffer do teclado
    while (getchar() != '\n');
}

/**
 * @brief Função auxiliar que pausa o programa (espera que o utilizador precione enter para continuar).
 * 
 */
void Pausar() {
    LimpaBuffer();
    printf("\nENTER para continuar...");
    getchar();
}
