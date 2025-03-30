/**
 * @file dados.h
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief Ficheiro com a efinição das constantes e das estruturas do projeto.
 * @version 0.1
 * @date 30-03-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "includes.h"

#define TAMNEF 5
#define EMPTY '.'
#define NEF '#'
#define SPACE ' '

typedef struct Antena {
    char frequencia;
    int x, y;
    struct Antena* next;
} Antena;

typedef struct EfeitoNefasto {
    int x, y;
    struct EfeitoNefasto* next;
} EfeitoNefasto;

typedef struct Matriz {
    int linhas, colunas;
} Matriz;
