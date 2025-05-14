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

// depois posso colocar o numero de nefastos
typedef struct Antena {
    DadosAntena dados;
    Nefasto* nefHead;
    struct Antena* prev;
    struct Antena* next;
} Antena;

// depois posso colocar o numerop de antenas
typedef struct TipoFreq {
    char freq;
    Antena* antHead;
    struct TipoFreq* next;
} TipoFreq;

typedef struct Grafo {
    int totalFreq;
    int totalAntenas;
    int totalNefastos;
    TipoFreq* grafoHead;
} Grafo;

// estruturas auxiliares
typedef struct DadosMatriz {
    int linhas, colunas;
} DadosMatriz;

typedef struct Coordenadas {
    int x, y;
} Coordenadas;
