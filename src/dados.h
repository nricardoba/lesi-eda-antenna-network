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

#define NEF '#'             // efeito nefasto
#define SBP '@'             // sobreposição de antena e efeito nefasto
#define VAZIO '.'           // espaço vazio
#define SPACE ' '           // caracter espaço
#define END_LINE '\n'       // caracter de fim de linha

#define MAX_MATRIZ 30       // maximo de linhas e colunas da matriz
#define DIS_NEF 5           // destancia minima para acontecer efeito nefasto

#pragma region Estruturas de Dados

/**
 * @brief Estrutura que contém os dados de uma antena (coordenadas e frequência).
 * 
 */
typedef struct DadosAntena {
    char freq;
    int x, y;
} DadosAntena;

/**
 * @brief Estrutura para guardar as dimensões da matriz (linhas e colunas).
 * 
 */
typedef struct DadosMatriz {
    int linhas, colunas;
} DadosMatriz;

/**
 * @brief Estrutura auxiliar que guarda as coordenadas de um vertice (posição na matriz).
 * 
 */
typedef struct Coordenadas {
    int x, y;
} Coordenadas;

#pragma endregion
#pragma region Antenas

/**
 * @brief Estrutura para criar uma lista ligada de antenas, guarda tambem as listas ligadas das suas respetivas antenas adjuntas e efeitos nefastos.
 * 
 */
typedef struct Antena {
    DadosAntena dados;
    int visitado;
    struct Adj* adjHead;
    struct Nefasto* nefHead;
    struct Antena* prev;
    struct Antena* next;
} Antena;

/**
 * @brief Estrutura para guardar a lista ligada de antenas adjuntas de uma antena.
 * 
 */
typedef struct Adj {
    DadosAntena dados;
    struct Antena* original;
    struct Adj* prev;
    struct Adj* next;
} Adj;

/**
 * @brief Estrutura para guardar a lista ligada de efeitos nefastos de uma antena.
 * 
 */
typedef struct Nefasto {
    DadosAntena dados;
    struct Antena* parente;
    struct Nefasto* next;
} Nefasto;

#pragma endregion
#pragma region Stack

/**
 * @brief Estrutura para guardar uma stack de antenas (utilizado em travessias).
 * 
 */
typedef struct VerticeStack {
    struct Antena* antena;
    struct VerticeStack* next;
} VerticeStack;

typedef struct VerticeQueue {
    struct Antena* antena;
    struct VerticeQueue* next;
} VerticeQueue;

#pragma endregion
