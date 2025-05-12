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

void LimpaTerminal() {

    #ifdef _WIN32           // windows
        system("cls");
    
    #else                   // mac ou linux
        system("clear");
        
    #endif
}

void LimpaBuffer() {
    // limpa o buffer do teclado
    while (getchar() != '\n');
}

void Pausar() {
    LimpaBuffer();
    printf("\nENTER para continuar...");
    getchar();
}
