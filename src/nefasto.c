/**
 * @file nefasto.c
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief Ficheiro que gere as funções sobre a lista ligada relativa ao efeito nefasto.
 * @version 0.1
 * @date 30-03-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "includes.h"

Nefasto* CriaNefasto(DadosAntena valores) {
    Nefasto* aux = (Nefasto*)malloc(sizeof(Nefasto));

    if (aux) {
        aux->dados = valores;

        aux->next = NULL;
    }

    return aux;
}

Nefasto* InsereNefasto(Nefasto* nefHead, Nefasto* novo) {
    if (!novo) return nefHead;

    if (!nefHead) {
        nefHead = novo;
        return nefHead;
    }

    Nefasto* aux = nefHead;
    while (aux->next) {
        aux = aux->next;
    }

    aux->next = novo;

    return nefHead;
}

Nefasto* EncontraNefasto(Nefasto* nefhead, int x, int y) {
    Nefasto* aux = nefhead;
    while (aux) {
        if (aux->dados.x == x && aux->dados.y == y) return aux;

        aux = aux->next;
    }

    return NULL;
}

// vais ter de fazer os dois ao mesmo tempo
bool CriaInsereNefasto(Antena* atual, Antena* comp, DadosMatriz matriz) {
    // se as duas antenas não causarem efeito nefasto, não ha nada para registar
    if (!CausaNefasto(atual, comp)) return false;

    for (int i = 0; i < 2; i++) {
        Antena* a = NULL;
        Antena* b = NULL;

        if (i == 0) {
            a = atual;
            b = comp;
        }
        else if (i == 1) {
            a = comp;
            b = atual;
        }

        int novoX = a->dados.x + (a->dados.x - b->dados.x);
        int novoY = a->dados.y + (a->dados.y - b->dados.y);

        if (EncontraNefasto(a->nefHead, novoX, novoY) || !CabeNaMatriz(matriz, novoX, novoY))
            return false;

        // não sei se é necessario
        DadosAntena dadosTemp;
        dadosTemp.freq = a->dados.freq;
        dadosTemp.x = novoX;
        dadosTemp.y = novoY;

        Nefasto* aux = CriaNefasto(dadosTemp);
        if (!aux) return false;

        a->nefHead = InsereNefasto(a->nefHead, aux);
        if (!a->nefHead) return false;

        return true;
    }
}

bool GeraNefasto(Antena* grafoHead, DadosMatriz matriz) {
    if (!grafoHead) return false;

    Antena* atual = grafoHead;
    while (atual) {
        Antena* comp = grafoHead;
        while (comp) {
            CriaInsereNefasto(atual, comp, matriz);

            comp = comp->next;
        }

        atual = atual->next;
    }
}

Nefasto* DestroiNefasto(Nefasto* nefHead) {
    if (!nefHead) return NULL;

    Nefasto* aux = NULL;
    while (nefHead) {
        aux = nefHead;
        nefHead = nefHead->next;
        free(aux);
    }

    return nefHead;
}

bool CausaNefasto(Antena* a, Antena* b) {
    // são a mesma antena
    if (a == b) return false;

    // se não tiverem a mesma frequencia, não ha efeito nefasto
    if (a->dados.freq != b->dados.freq) return false;

    // valor absoluto
    int difX = abs(a->dados.x - b->dados.x);
    int difY = abs(a->dados.y - b->dados.y);

    if (difX + difY > DIS_NEF) return false;

    return true;
}

bool ExisteNefasto(Antena* grafoHead, int x, int y) {
    if (!grafoHead) return false;

    Antena* antAux = grafoHead;
    while (antAux) {
        Nefasto* nefAux = antAux->nefHead;
        while (nefAux) {
            if (nefAux->dados.x == x && nefAux->dados.y == y)
                return true;

            nefAux = nefAux->next;
        }

        antAux = antAux->next;
    }

    return false;
}
