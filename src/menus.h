/**
 * @file menus.h
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief Headerfile do ficheiro menus.c
 * @version 0.1
 * @date 30-03-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "includes.h"

bool CriaMatriz(Matriz* m);
bool ExisteMatriz(int x, int y);
int PreMenu();
int MainMenu();
bool ExecPreMenu(Antena** head, EfeitoNefasto** inicioNef, Matriz* m);
Antena* ExecMainMenu(Antena* head, EfeitoNefasto** inicioNef, Matriz m, bool* term);
