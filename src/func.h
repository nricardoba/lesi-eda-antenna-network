/**
 * @file func.h
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief Headerfile do ficheiro func.c
 * @version 0.1
 * @date 30-03-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "includes.h"

Antena* CriaAntena(DadosAntena valores);
Antena* InsereAntena(Antena* antenaHead, Antena* novo);
Antena* RemoveAntena(Antena* antenaHead, int x, int y);
Antena* EncontraAntena(Antena* antenaHead, int x, int y);
Antena* DestroiAntenas(Antena* antenaHead);
bool ValidaCharAntena(char letra);

// matriz
bool CabeNaMatriz(DadosMatriz matriz, int x, int y);
bool ValidaMatriz(DadosMatriz matriz);
