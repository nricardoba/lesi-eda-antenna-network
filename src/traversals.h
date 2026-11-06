/**
 * @file traversals.h
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief Header file for traversals.c.
 * @version 0.1
 * @date 18-05-2025
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "includes.h"

VertexQueue *QueuePush(VertexQueue *tail, Antenna *current);
Antenna *QueuePop(VertexQueue **head);
bool VisitAdjacenciesBFS(Antenna *graphHead, Antenna *start);
bool PromptVisitBFS(Antenna *graphHead);

VertexStack *StackPush(VertexStack *head, Antenna *current);
Antenna *StackPop(VertexStack **head);
bool VisitAdjacenciesDFS(Antenna *graphHead, Antenna *start);
bool PromptVisitDFS(Antenna *graphHead);

bool ResetVisited(Antenna *graphHead);
