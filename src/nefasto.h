/**
 * @file nefasto.h
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief Headerfile do ficheiro nefasto.c
 * @version 0.1
 * @date 30-03-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "includes.h"

Nefasto* CriaNefasto(DadosAntena valores);
Nefasto* InsereNefasto(Nefasto* nefastoHead, Nefasto* novo);
Nefasto* EncontraNefasto(Nefasto* nefastoHead, int x, int y);
Nefasto* CriaInsereNefasto(Nefasto* nefastoHead, DadosMatriz matriz, Antena atual, Antena comparador);
Nefasto* GeraNefasto(Antena* antenaHead, Nefasto* nefastoHead, DadosMatriz matriz);
Nefasto* DestroiNefasto(Nefasto* nefastoHead);
bool CausaNefasto(Antena a1, Antena a2);
bool ExisteNefasto(Nefasto* nefastoHead, int x, int y, Antena* antenaPai);
