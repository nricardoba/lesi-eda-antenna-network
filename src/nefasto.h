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

EfeitoNefasto* CriaNefasto(int x, int y);
EfeitoNefasto* InsereNefasto(EfeitoNefasto* inicio, EfeitoNefasto* novo);
EfeitoNefasto* GeraNefasto(EfeitoNefasto* inicioNefasto, Antena* head, Matriz m);
EfeitoNefasto* EncontraNefasto(EfeitoNefasto* inicioNef, int x, int y);
bool VerificaNefasto(Antena antena1, Antena antena2, int* distancia);
bool ExisteNefasto(EfeitoNefasto* inicioNef, int x, int y);
void MostraMatrizNefasto(Antena* inicioAnt, EfeitoNefasto* inicioNef, Matriz m);
void MostraListaNefasto(EfeitoNefasto* inicio);
void DestroiListaNefasto(EfeitoNefasto** head);
