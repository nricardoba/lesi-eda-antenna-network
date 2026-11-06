/**
 * @file extra.c
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief Utility functions for the project.
 * @version 0.1
 * @date 18-05-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "includes.h"

/**
 * @brief Clears the terminal.
 * 
 */
void ClearTerminal() {

    #ifdef _WIN32           // windows
        system("cls");
    
    #else                   // mac or linux
        system("clear");
        
    #endif
}

/**
 * @brief Clears the keyboard input buffer.
 * 
 */
void ClearInputBuffer() {
    // clear the keyboard input buffer
    while (getchar() != '\n');
}

/**
 * @brief Pauses the program until the user presses Enter to continue.
 * 
 */
void Pause() {
    ClearInputBuffer();
    printf("\nENTER to continue...");
    getchar();
}
