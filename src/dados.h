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

#define TAMNEF 5        // tamanho maximo para existir efeito nefasto
#define EMPTY '.'       // simbolo para um espaço vazio na matriz
#define NEF '#'         // simbolo que representa um efeito nefasto
#define SUBP '@'        // simbolo que representa uma sobreposição de uma antena e um efeito nefasto
#define SPACE ' '       // simbolo que representa um espaço

typedef struct DadosAntena {
    char frequencia;
    int x, y;
} DadosAntena;

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
