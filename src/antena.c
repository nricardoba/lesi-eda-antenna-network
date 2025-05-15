/**
 * @file antena.c
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 14-05-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "includes.h"

#pragma region Funções Antenas

Antena* CriaAntena(DadosAntena valores) {
    Antena* aux = (Antena*)malloc(sizeof(Antena));

    // se conseguiu alocar memoria
    if (aux) {
        aux->dados = valores;

        aux->adjHead = NULL;
        aux->nefHead = NULL;
        aux->prev = NULL;
        aux->next = NULL;
    }

    return aux;
}

Antena* InsereAntena(Antena* grafoHead, Antena* novo) {
    // se não existir uma nova antena, não ha nada para inserir
    if (!novo) return grafoHead;

    // se não houver uma lista, a nova antena é a primeira
    if (!grafoHead) {
        grafoHead = novo;
        return grafoHead;
    }

    // percorrer a lista até ao fim
    Antena* aux = grafoHead;
    while (aux->next) {
        aux = aux->next;
    }

    // inserir a nova antena no final da lista
    aux->next = novo;
    novo->prev = aux;

    return grafoHead;
}

Antena* RemoveAntena(Antena* grafoHead, Antena* alvo) {
    // se não houver lista, não ha nada para remover
    if (!grafoHead || !alvo) return grafoHead;

    // desstruir as listas de adj e nef do alvo
    alvo->adjHead = DestroiAdj(alvo->adjHead);
    alvo->nefHead = DestroiNefasto(alvo->nefHead);

    // no caso de a antena a remover se o inicio da lista
    if (grafoHead == alvo) {
        grafoHead = grafoHead->next;
        if (grafoHead) grafoHead->prev = NULL;
        free(alvo);

        return grafoHead;
    }

    if (alvo->prev) alvo->prev->next = alvo->next;
    if (alvo->next) alvo->next->prev = alvo->prev;
    free(alvo);

    return grafoHead;
}

Antena* EncontraAntena(Antena* grafoHead, int x, int y) {
    Antena* aux = grafoHead;
    while (aux) {
        if (aux->dados.x == x && aux->dados.y == y) return aux;

        aux = aux->next;
    }

    return NULL;
}

Antena* DestroiAntenas(Antena* grafoHead) {
    if (!grafoHead) return NULL;

    Antena* aux = NULL;
    while (grafoHead) {
        aux = grafoHead;
        grafoHead = grafoHead->next;

        // destroi a lista de adj deste vertice
        aux->adjHead = DestroiAdj(aux->adjHead);

        // destroi a lista de nefasto deste vertice
        aux->nefHead = DestroiNefasto(aux->nefHead);

        free(aux);
    }

    return grafoHead;
}

#pragma endregion
#pragma region Funções Adj

Adj* CriaAdj(DadosAntena valores) {
    Adj* aux = (Adj*)malloc(sizeof(Adj));

    // se conseguiu alocar memoria
    if (aux) {
        aux->dados = valores;

        aux->original = NULL;
        aux->prev = NULL;
        aux->next = NULL;
    }

    return aux;
}

Adj* InsereAdj(Adj* adjHead, Adj* novo) {
    if (!novo) return adjHead;

    if (!adjHead) {
        adjHead = novo;
        return adjHead;
    }

    Adj* aux = adjHead;
    while (aux->next) {
        aux = aux->next;
    }

    aux->next = novo;
    novo->prev = aux;

    return adjHead;
}

Adj* RemoveAdj(Adj* adjHead, Adj* alvo) {
    if (!adjHead || !alvo) return adjHead;

    if (adjHead == alvo) {
        adjHead = adjHead->next;
        if (adjHead) adjHead->prev = NULL;
        free(alvo);

        return adjHead;
    }

    if (alvo->prev) alvo->prev->next = alvo->next;
    if (alvo->next) alvo->next->prev = alvo->prev;
    free(alvo);

    return adjHead;
}

Adj* EncontraAdj(Adj* adjHead, int x, int y) {
    Adj* aux = adjHead;
    while (aux) {
        if (aux->dados.x == x && aux->dados.y == y) return aux;

        aux = aux->next;
    }

    return NULL;
}

Adj* DestroiAdj(Adj* adjHead) {
    if (!adjHead) return NULL;

    Adj* aux = NULL;
    while (adjHead) {
        aux = adjHead;
        adjHead = adjHead->next;
        free(aux);
    }

    return adjHead;
}

#pragma endregion
