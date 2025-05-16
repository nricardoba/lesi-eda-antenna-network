/**
 * @file antena.h
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 14-05-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "includes.h"

Antena* CriaAntena(DadosAntena valores);
Antena* InsereAntena(Antena* grafoHead, Antena* novo);
Antena* InsereAntenaOrdenado(Antena* grafoHead, Antena* novo);
Antena* RemoveAntena(Antena* grafoHead, Antena* alvo);
Antena* EncontraAntena(Antena* grafoHead, int x, int y);
Antena* DestroiAntenas(Antena* grafoHead);

Adj* CriaAdj(DadosAntena valores, Antena* original);
Adj* InsereAdj(Adj* adjHead, Adj* novo);
Adj* InsereAdjOrdenado(Adj* adjHead, Adj* novo);
Adj* RemoveAdj(Adj* adjHead, Adj* alvo);
Adj* EncontraAdj(Adj* adjHead, int x, int y);
Adj* DestroiAdj(Adj* adjHead);
bool CausaAdj(Antena* a, Antena* b);

bool GeraAdj(Antena* grafoHead);
bool RemoveOutrasAdj(Antena* grafoHead, Antena* alvo);
