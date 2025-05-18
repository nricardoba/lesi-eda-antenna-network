/**
 * @file travessias.c
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 18-05-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "includes.h"

bool VisitaAdjDFS(Antena* grafoHead, Antena* inicio) {
    if (!grafoHead || !inicio) return false;

    return true;
}

bool ResetVisitados(Antena* grafoHead) {
    if (!grafoHead) return false;

    Antena* aux = grafoHead;
    while (aux) {
        aux->visitado = 0;
        aux = aux->next;
    }

    return true;
}
