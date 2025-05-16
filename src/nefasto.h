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

Nefasto* CriaNefasto(DadosAntena valores, Antena* parente);
Nefasto* InsereNefasto(Nefasto* nefHead, Nefasto* novo);
Nefasto* InsereNefastoOrdenado(Nefasto* nefHead, Nefasto* novo);
Nefasto* RemoveNefasto(Nefasto* nefHead, Nefasto* alvo);
Nefasto* EncontraNefasto(Nefasto* nefhead, Antena* parente, int x, int y);
bool CriaInsereNefasto(Antena* atual, Antena* comp, DadosMatriz matriz);
bool GeraNefasto(Antena* grafoHead, DadosMatriz matriz);
Nefasto* DestroiNefasto(Nefasto* nefHead);

bool CausaNefasto(Antena* a, Antena* b);
bool ExisteNefasto(Antena* grafoHead, int x, int y);
bool RemoveOutrosNefastos(Antena* grafoHead, Antena* alvo);
