/**
 * @file func.c
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief Ficheiro que gere as funções sobre a lista ligada relativa às antenas.
 * @version 0.1
 * @date 30-03-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "includes.h"

Antena* CriaAntena(DadosAntena valores) {
    Antena* aux = (Antena*)malloc(sizeof(Antena));

    // se conseguiu alocar memoria
    if (aux) {
        aux->dados.freq = valores.freq;
        aux->dados.x = valores.x;
        aux->dados.y = valores.y;

        aux->next = NULL;
    }

    return aux;
}

// depois fazer uma versão em que insere ordenado
Antena* InsereAntena(Antena* antenaHead, Antena* novo) {
    // se não existir uma nova antena, não ha nada para inserir
    if (!novo) return antenaHead;

    // se não houver uma lista, a nova antena é a primeira
    if (!antenaHead) {
        antenaHead = novo;
        return antenaHead;
    }

    // percorrer a lista até ao fim
    Antena* aux = antenaHead;
    while (aux->next) {
        aux = aux->next;
    }

    // inserir a nova antena no final da lista
    aux->next = novo;

    return antenaHead;
}

// verificar se da para eliminar a head ou a seguinte
Antena* RemoveAntena(Antena* antenaHead, int x, int y) {
    // se não houver lista, não ha nada para remover
    if (!antenaHead) return NULL;

    // no caso de a antena a remover se o inicio da lista
    if (antenaHead->dados.x == x && antenaHead->dados.y == y) {
        Antena* aux = antenaHead;
        antenaHead = antenaHead->next;
        free(aux);

        return antenaHead;
    }

    Antena* atual = antenaHead->next;
    Antena* anterior = antenaHead;

    while (atual) {
        if (atual->dados.x == x && atual->dados.y == y) {
            anterior->next = atual->next;
            free(atual);

            return antenaHead;
        }

        anterior = atual;
        atual = atual->next;
    }

    return antenaHead;
}

Antena* EncontraAntena(Antena* antenaHead, int x, int y) {
    Antena* aux = antenaHead;
    while (aux) {
        if (aux->dados.x == x && aux->dados.y == y) return aux;

        aux = aux->next;
    }

    return NULL;
}

Antena* DestroiAntenas(Antena* antenaHead) {
    if (!antenaHead) return NULL;

    Antena* aux = NULL;
    while (antenaHead) {
        aux = antenaHead;
        antenaHead = antenaHead->next;
        free(aux);
    }

    return antenaHead;
}

bool ValidaCharAntena(char letra) {
    if (letra != VAZIO && letra != NEF && letra != SBP && letra != SPACE && letra != END_LINE) return true;
    return false;
}

bool CabeNaMatriz(DadosMatriz matriz, int x, int y) {
    // nenhuma coordenada pode ser <= 0
    if (x <= 0 || y <= 0) return false;

    // tem que ser menor do que o numero de linhas e colunas da matriz
    if (x <= matriz.linhas && y <= matriz.colunas) return true;

    return false;
}

bool ValidaMatriz(DadosMatriz matriz) {
    // o numero de linhas e de colunas não pode ser menor ou igual a 0
    if (matriz.linhas <= 0 || matriz.colunas <= 0) return false;

    // o numero de linhas e colunas, não pode exeder o maximo
    if (matriz.linhas <= MAX_MATRIZ && matriz.colunas <= MAX_MATRIZ) return true;

    return false;
}
