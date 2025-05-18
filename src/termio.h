/**
 * @file termio.h
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief Headerfile do ficheiro "termio.c".
 * @version 0.1
 * @date 18-05-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "includes.h"

Antena* CriaInsereAntena(Antena* grafoHead, DadosMatriz matriz);
Antena* PerguntaRemoveAntena(Antena* grafoHead);
Antena* AlteraAntena(Antena* grafoHead, DadosMatriz matriz);
bool MostraListaAntenas(Antena* grafoHead);
bool MostraMatrizAntenas(Antena* grafoHead, DadosMatriz matriz);

bool MostraListaAdj(Antena* alvo);
bool EscolheMostraAdj(Antena* grafoHead);

bool MostraListaNefasto(Antena* alvo);
bool EscolheMostraNefasto(Antena* grafoHead);
bool MostraTodosNefastos(Antena* grafoHead);
bool MostraMatrizNefasto(Antena* grafoHead, DadosMatriz matriz);

Antena* LerFicheiroMatriz(char* ficheiro, Antena* grafoHead, DadosMatriz* matriz);
bool GuardarFicheiroMatriz(char* ficheiro, Antena* grafoHead, DadosMatriz matriz);
DadosMatriz CriaMatriz(DadosMatriz matriz);
Coordenadas PedeCoordenadas(char* mensagem);
