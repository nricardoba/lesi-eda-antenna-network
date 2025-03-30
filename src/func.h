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

Antena* CriaAntena(int x, int y, char c);
Antena* InsereAntena(Antena* head, Antena* novo);
Antena* AlteraAntena(Antena* head, Matriz m);
Antena* RemoveAntena(Antena* head, int x, int y);
Antena* CriaInsereAntena(Antena* head, Matriz m);
Antena* PerguntaRemoveAntena(Antena* head);
bool CabeNaMatriz(Matriz m, int x, int y);
bool ExisteAntena(Antena* head, int x, int y);
Antena* EncontraAntena(Antena* head, int x, int y);
void MostraMatrizAntenas(Antena* head, Matriz m);
void MostraListaAntenas(Antena* head);
bool LerFicheiroMatriz(Antena** head, Matriz* m);
void GuardarFicheiroMatriz(Antena* head, Matriz m);
void DestroiListaAntenas(Antena** head);
bool ValidaCharAntena(char letra);
