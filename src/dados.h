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

typedef struct Nefasto {
    DadosAntena dados;
    struct Nefasto* next;
} Nefasto;

typedef struct AdjAntena {
    DadosAntena dados;
    struct AdjAntena* prev;     // ainda não sei se é necessario
    struct AdjAntena* next;
} AdjAntena;

// depois posso colocar o numero de nefastos
typedef struct Antena {
    DadosAntena dados;
    AdjAntena* adjHead;
    Nefasto* nefHead;
    struct Antena* prev;
    struct Antena* next;
} Antena;

// estruturas auxiliares
typedef struct DadosMatriz {
    int linhas, colunas;
} DadosMatriz;

typedef struct Coordenadas {
    int x, y;
} Coordenadas;
