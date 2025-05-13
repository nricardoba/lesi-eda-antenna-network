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

    // se conseguiu alocar memoria
    if (aux) {
        aux->dados.freq = valores.freq;
        aux->dados.x = valores.x;
        aux->dados.y = valores.y;

        aux->antenaPai = NULL;
        aux->primo = NULL;
        aux->prev = NULL;
        aux->next = NULL;
    }

    return aux;
}

Nefasto* InsereNefasto(Nefasto* nefastoHead, Nefasto* novo) {
    if (!novo) return nefastoHead;

    if (!nefastoHead) {
        nefastoHead = novo;
        return nefastoHead;
    }

    Nefasto* aux = nefastoHead;
    while (aux->next) {
        aux = aux->next;
    }

    aux->next = novo;
    novo->prev = aux;

    return nefastoHead;
}

Nefasto* EncontraNefasto(Nefasto* nefastoHead, int x, int y) {
    Nefasto* aux = nefastoHead;
    while (aux) {
        if (aux->dados.x == x && aux->dados.y == y) return aux;

        aux = aux->next;
    }

    return NULL;
}

Nefasto* CriaInsereNefasto(Nefasto* nefastoHead, DadosMatriz matriz, Antena atual, Antena comparador) {
    // se as duas antenas não causarem efeito nefasto, não ha nada para registar
    if (!CausaNefasto(atual, comparador)) return nefastoHead;

    // criação das coordenadas do novo efeito nefasto
    int novoX = atual.dados.x + (atual.dados.x - comparador.dados.x);
    int novoY = atual.dados.y + (atual.dados.y - comparador.dados.y);

    // se já existir um efeito nefasto nessas coordenadas com essa antena pai,
    // ou as coordenadas não pertencerem à matriz, não ha nada a registar
    if (ExisteNefasto(nefastoHead, novoX, novoY, &atual) || !CabeNaMatriz(matriz, novoX, novoY))
        return nefastoHead;

    DadosAntena dadosTemp;
    dadosTemp.x = novoX;
    dadosTemp.y = novoY;
    dadosTemp.freq = atual.dados.freq;

    Nefasto* aux = CriaNefasto(dadosTemp);
    if (!aux) return nefastoHead;

    aux->antenaPai = &atual;
    nefastoHead = InsereNefasto(nefastoHead, aux);

    return nefastoHead;
}

Nefasto* GeraNefasto(Antena* antenaHead, Nefasto* nefastoHead, DadosMatriz matriz) {
    if (!antenaHead) return NULL;

    Antena* atual = antenaHead;
    while (atual) {
        Antena* comparador = antenaHead;
        while (comparador) {
            nefastoHead = CriaInsereNefasto(nefastoHead, matriz, *atual, *comparador);

            comparador = comparador->next;
        }

        atual = atual->next;
    }

    return nefastoHead;
}

Nefasto* DestroiNefasto(Nefasto* nefastoHead) {
    if (!nefastoHead) return NULL;

    Nefasto* aux = NULL;
    while (nefastoHead) {
        aux = nefastoHead;
        nefastoHead = nefastoHead->next;
        free(aux);
    }

    return nefastoHead;
}

bool CausaNefasto(Antena a1, Antena a2) {
    // se não tiverem a mesma frequencia, não ha efeito nefasto
    if (a1.dados.freq != a2.dados.freq) return false;

    // são a mesma antena
    if (a1.dados.x == a2.dados.x && a1.dados.y == a2.dados.y) return false;

    // valor absoluto
    int difX = abs(a1.dados.x - a2.dados.x);
    int difY = abs(a1.dados.y - a2.dados.y);

    if (difX + difY > DIS_NEF) return false;

    return true;
}

bool ExisteNefasto(Nefasto* nefastoHead, int x, int y, Antena* antenaPai) {
    if (!nefastoHead || !antenaPai) return false;

    Nefasto* aux = nefastoHead;
    while (aux) {
        if (aux->dados.x == x && aux->dados.y == y && aux->antenaPai == antenaPai)
            return true;

        aux = aux->next;
    }

    return false;
}
