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

#define NEF '#'
#define SBP '@'
#define VAZIO '.'
#define SPACE ' '
#define END_LINE '\n'

#define MAX_MATRIZ 30
#define DIS_NEF 5

typedef struct DadosAntena {
    char freq;
    int x, y;
} DadosAntena;

typedef struct Antena {
    DadosAntena dados;
    struct Antena* prev;
    struct Antena* next;
} Antena;

typedef struct Nefasto {
    DadosAntena dados;
    Antena* antenaPai;
    struct Nefasto* primo;
    struct Nefasto* prev;
    struct Nefasto* next;
} Nefasto;

typedef struct DadosMatriz {
    int linhas, colunas;
} DadosMatriz;

typedef struct Coordenadas {
    int x, y;
} Coordenadas;
