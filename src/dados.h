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

#pragma region Estruturas de Dados

typedef struct DadosAntena {
    char freq;
    int x, y;
} DadosAntena;

typedef struct DadosMatriz {
    int linhas, colunas;
} DadosMatriz;

typedef struct Coordenadas {
    int x, y;
} Coordenadas;

#pragma endregion

typedef struct Antena {
    DadosAntena dados;
    struct Adj* adjHead;
    struct Nefasto* nefHead;
    struct Antena* prev;
    struct Antena* next;
} Antena;

typedef struct Adj {
    DadosAntena dados;
    struct Antena* original;
    struct Adj* prev;
    struct Adj* next;
} Adj;

typedef struct Nefasto {
    DadosAntena dados;
    struct Antena* parente;
    struct Nefasto* next;
} Nefasto;
