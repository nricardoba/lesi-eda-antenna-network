/**
 * @file func.c
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief Ficheiro com funções auxiliares do projeto.
 * @version 0.1
 * @date 18-05-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "includes.h"

/**
 * @brief Verifica se um vertive cabe na matriz.
 * 
 * @param matriz Dados da matriz.
 * @param x Coordenada x para verificar.
 * @param y Coordenada y para verificar.
 * @return true Se cabe na matriz.
 * @return false Se não cabe na matriz.
 */
bool CabeNaMatriz(DadosMatriz matriz, int x, int y) {
    // nenhuma coordenada pode ser <= 0
    if (x <= 0 || y <= 0) return false;

    // tem que ser menor do que o numero de linhas e colunas da matriz
    if (x <= matriz.linhas && y <= matriz.colunas) return true;

    return false;
}

/**
 * @brief Verifica as dimensões de uma matriz são validas.
 * 
 * @param matriz Dados da matriz.
 * @return true Se as dimensões são validas.
 * @return false Se as dimensões são invalidas.
 */
bool ValidaMatriz(DadosMatriz matriz) {
    // o numero de linhas e de colunas não pode ser menor ou igual a 0
    if (matriz.linhas <= 0 || matriz.colunas <= 0) return false;

    // o numero de linhas e colunas, não pode exeder o maximo
    if (matriz.linhas <= MAX_MATRIZ && matriz.colunas <= MAX_MATRIZ) return true;

    return false;
}

/**
 * @brief Valida de um caracter pode representar a frequência de uma antena.
 * 
 * @param letra Caracter pretendido.
 * @return true Se pode representar.
 * @return false Se não é valido.
 */
bool ValidaCharAntena(char letra) {
    if (letra != VAZIO && letra != NEF && letra != SBP && letra != SPACE && letra != END_LINE) return true;
    return false;
}
