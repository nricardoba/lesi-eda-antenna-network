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

VerticeQueue* QueuePush(VerticeQueue* tail, Antena* atual);
Antena* QueuePop(VerticeQueue** head);
bool VisitaAdjBFS(Antena* grafoHead, Antena* inicio);
bool PerguntaVisitaBFS(Antena* grafoHead);

VerticeStack* StackPush(VerticeStack* head, Antena* atual);
Antena* StackPop(VerticeStack** head);
bool VisitaAdjDFS(Antena* grafoHead, Antena* inicio);
bool PerguntaVisitaDFS(Antena* grafoHead);

bool ResetVisitados(Antena* grafoHead);
