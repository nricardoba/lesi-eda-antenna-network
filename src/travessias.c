/**
 * @file travessias.c
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief Ficheiro que gere as funções sobre travessias do projeto.
 * @version 0.1
 * @date 18-05-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "includes.h"

bool VisitaAdjDFS(Antena* grafoHead, Antena* inicio) {
    if (!grafoHead || !inicio) return false;

    ResetVisitados(grafoHead);
    
    VerticeStack* stackHead = NULL;

    // coloca a antena inicial na stack
    stackHead = StackPush(stackHead, inicio);

    while (stackHead) {
        Antena* atual = StackPop(&stackHead);
        if (!atual->visitado) {
            atual->visitado = 1;
            Adj* adj = atual->adjHead;
            while (adj) {
                if (adj->original && !adj->original->visitado) {
                    stackHead = StackPush(stackHead, adj->original);
                }
                adj = adj->next;
            }
        }
    }

    return true;
}

VerticeStack* StackPush(VerticeStack* topo, Antena* atual) {
    VerticeStack* novo = (VerticeStack*)malloc(sizeof(VerticeStack));
    if (!novo) return topo;

    novo->antena = atual;
    novo->next = topo;

    return novo;
}

Antena* StackPop(VerticeStack** topo) {
    if (!*topo) return NULL;

    VerticeStack* temp = *topo;
    Antena* antena = temp->antena;
    *topo = temp->next;
    free(temp);

    return antena;
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
