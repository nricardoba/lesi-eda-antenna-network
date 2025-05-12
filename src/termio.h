/**
 * @file termio.h
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 11-05-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "includes.h"

Antena* CriaInsereAntena(Antena* antenaHead, DadosMatriz matriz);
Antena* PerguntaRemoveAntena(Antena* antenaHead);
Antena* AlteraAntena(Antena* antenaHead, DadosMatriz matriz);
bool MostraListaAntenas(Antena* antenaHead);
bool MostraMatrizAntenas(Antena* antenaHead, DadosMatriz matriz);
Antena* LerFicheiroMatriz(char* ficheiro, Antena* antenaHead, DadosMatriz* matriz);
bool GuardarFicheiroMatriz(char* ficheiro, Antena* antenaHead, DadosMatriz matriz);
DadosMatriz CriaMatriz(DadosMatriz matriz);
Coordenadas PedeCoordenadas(char* mensagem);
