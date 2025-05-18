/**
 * @file nefasto.c
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief Ficheiro que gere as funções sobre efeitos nefastos do projeto.
 * @version 0.1
 * @date 18-05-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "includes.h"

/**
 * @brief Cria um novo efeito nefasto com os dados passados por parametros.
 * 
 * @param valores Dados do efeito nefasto.
 * @param parente Antena que gerou o efeito nefasto.
 * @return Nefasto* Novo efeito nefasto criado.
 */
Nefasto* CriaNefasto(DadosAntena valores, Antena* parente) {
    Nefasto* aux = (Nefasto*)malloc(sizeof(Nefasto));

    if (aux) {
        aux->dados = valores;
        aux->parente = parente;

        aux->next = NULL;
    }

    return aux;
}

/**
 * @brief Insere um novo efeito nefasto na lista de uma antena.
 * 
 * @param nefHead Inicio da lista de efeito nefasto de uma antena.
 * @param novo Novo efeito nefasto a inserir.
 * @return Nefasto* Inicio da lista de efeito nefasto atualizada.
 */
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

/**
 * @brief Insere um novo efeito nefasto, ordenado, na lista de uma antena.
 * 
 * @param nefHead Inicio da lista de efeito nefasto de uma antena.
 * @param novo Novo efeito nefasto a inserir.
 * @return Nefasto* Inicio da lista de efeito nefasto atualizada.
 */
Nefasto* InsereNefastoOrdenado(Nefasto* nefHead, Nefasto* novo) {
    if (!novo) return nefHead;

    // Se a lista estiver vazia ou o novo deve ser o primeiro
    if (!nefHead ||
        (novo->dados.x < nefHead->dados.x) ||
        (novo->dados.x == nefHead->dados.x && novo->dados.y < nefHead->dados.y)) {
        novo->next = nefHead;
        return novo;
    }

    Nefasto* aux = nefHead;
    while (aux->next &&
          ((aux->next->dados.x < novo->dados.x) ||
           (aux->next->dados.x == novo->dados.x && aux->next->dados.y < novo->dados.y))) {
        aux = aux->next;
    }

    novo->next = aux->next;
    aux->next = novo;

    return nefHead;
}

/**
 * @brief Remove um efeito nefasto de uma lista.
 * 
 * @param nefHead Inicio da lista de efeito nefasto de uma antena.
 * @param alvo Antena a Remover.
 * @return Nefasto* Inicio da lista de efeito nefasto atualizada.
 */
Nefasto* RemoveNefasto(Nefasto* nefHead, Nefasto* alvo) {
    if (!nefHead || !alvo) return nefHead;

    if (nefHead == alvo) {
        nefHead = nefHead->next;
        free(alvo);
        return nefHead;
    }

    Nefasto* aux = nefHead;
    while (aux->next && aux->next != alvo) {
        aux = aux->next;
    }

    if (aux->next == alvo) {
        aux->next = alvo->next;
        free(alvo);
    }

    return nefHead;
}

/**
 * @brief Encontra um efeito nefasto presente na lista de uma antena.
 * 
 * @param nefhead Inicio da lista de efeito nefasto de uma antena.
 * @param parente Antena que gerou o efeito nefasto.
 * @param x Coordenada x do efeito nefasto a encontrar.
 * @param y Coordenada y do efeito nefasto a encontrar.
 * @return Nefasto* Efeito nefasto encontrado (se não encontrou, devolve NULL).
 */
Nefasto* EncontraNefasto(Nefasto* nefhead, Antena* parente, int x, int y) {
    Nefasto* aux = nefhead;
    while (aux) {
        if (aux->parente == parente && aux->dados.x == x && aux->dados.y == y) return aux;

        aux = aux->next;
    }

    return NULL;
}

/**
 * @brief Calcula e insere uma efeito nefasto na lista de uma antena.
 * 
 * @param atual Antena atual.
 * @param comp Antena para comparar a existencia de efeito nefasto.
 * @param matriz Dados da matriz.
 * @return true Se consegui criar e inserir com sucesso.
 * @return false Se não conseguiu realizar a operação.
 */
bool CriaInsereNefasto(Antena* atual, Antena* comp, DadosMatriz matriz) {
    if (!atual || !comp) return false;

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

        if (!EncontraNefasto(atual->nefHead, comp, novoX, novoY) && CabeNaMatriz(matriz, novoX, novoY)) {
            DadosAntena dadosTemp;
            dadosTemp.freq = atual->dados.freq;
            dadosTemp.x = novoX;
            dadosTemp.y = novoY;

            Nefasto* aux = CriaNefasto(dadosTemp, comp);
            atual->nefHead = InsereNefastoOrdenado(atual->nefHead, aux);
        }
    }

    return true;
}

/**
 * @brief Gera a lista de efeito nefasto para todas as antenas.
 * 
 * @param grafoHead Inicio da lista das antenas.
 * @param matriz Dados da matriz.
 * @return true Se conseguiu gerar nefasto.
 * @return false Se não existe grafo.
 */
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

    return true;
}

/**
 * @brief Destroi a lista de efeito nefasto de uma antena.
 * 
 * @param nefHead Inicio da lista de efeito nefasto de uma antena.
 * @return Nefasto* Inicio da lista de efeito nefasto vazia.
 */
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

/**
 * @brief Verifica se existe efeito nefasto entre duas antenas.
 * 
 * @param a Primeira antena para comparar a existência de efeito nefasto.
 * @param b Segunda antena para comparar a existência de efeito nefasto.
 * @return true Se causa efeito nefasto.
 * @return false Se não causa efeito nefasto.
 */
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

/**
 * @brief Se existe pelo menos um efeito nefasto no grafo, com as coordenadas pretendidas.
 * 
 * @param grafoHead Inicio da lista das antenas.
 * @param x Coordenada x do efeito nefasto a encontrar.
 * @param y Coordenada y do efeito nefasto a encontrar.
 * @return true Se conseguiu encontrar.
 * @return false Se não conseguiu encontrar.
 */
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

/**
 * @brief Remove um efeito nefasto das listas das outras antenas.
 * 
 * @param grafoHead Inicio da lista das antenas.
 * @param alvo Antena parente do efeito nefasto a remover.
 * @return true Se conseguiu remover.
 * @return false Se não existe grafo ou alvo a remover.
 */
bool RemoveOutrosNefastos(Antena* grafoHead, Antena* alvo) {
    if (!grafoHead || !alvo) return false;

    Antena* antAux = grafoHead;
    while (antAux) {
        Nefasto* nefAux = antAux->nefHead;
        while (nefAux) {
            Nefasto* nextNef = nefAux->next;
            if (nefAux->parente == alvo) {
                antAux->nefHead = RemoveNefasto(antAux->nefHead, nefAux);
            }
            nefAux = nextNef;
        }

        antAux = antAux->next;
    }

    return true;
}
