/**
 * @file travessias.h
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief Headerfile do ficheiro "travessias.c".
 * @version 0.1
 * @date 18-05-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "includes.h"

bool VisitaAdjDFS(Antena* grafoHead, Antena* inicio);
VerticeStack* StackPush(VerticeStack* topo, Antena* atual);
Antena* StackPop(VerticeStack** topo);
bool ResetVisitados(Antena* grafoHead);
