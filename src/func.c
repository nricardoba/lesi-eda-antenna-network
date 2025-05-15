/**
 * @file func.c
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief Ficheiro que gere as funções sobre a lista ligada relativa às antenas.
 * @version 0.1
 * @date 30-03-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "includes.h"

bool CabeNaMatriz(DadosMatriz matriz, int x, int y) {
    // nenhuma coordenada pode ser <= 0
    if (x <= 0 || y <= 0) return false;

    // tem que ser menor do que o numero de linhas e colunas da matriz
    if (x <= matriz.linhas && y <= matriz.colunas) return true;

    return false;
}

bool ValidaMatriz(DadosMatriz matriz) {
    // o numero de linhas e de colunas não pode ser menor ou igual a 0
    if (matriz.linhas <= 0 || matriz.colunas <= 0) return false;

    // o numero de linhas e colunas, não pode exeder o maximo
    if (matriz.linhas <= MAX_MATRIZ && matriz.colunas <= MAX_MATRIZ) return true;

    return false;
}

bool ValidaCharAntena(char letra) {
    if (letra != VAZIO && letra != NEF && letra != SBP && letra != SPACE && letra != END_LINE) return true;
    return false;
}
