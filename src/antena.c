/**
 * @file antena.c
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief Ficheiro que gere as funções sobre antenas do projeto.
 * @version 0.1
 * @date 18-05-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "includes.h"

#pragma region Funções Antenas

/**
 * @brief Cria uma nova antena com os dados passados por parametro.
 * 
 * @param valores Dados da antena.
 * @return Antena* Apontador para a nova antena criada.
 */
Antena* CriaAntena(DadosAntena valores) {
    Antena* aux = (Antena*)malloc(sizeof(Antena));

    // se conseguiu alocar memoria
    if (aux) {
        aux->dados = valores;

        aux->visitado = 0;
        aux->adjHead = NULL;
        aux->nefHead = NULL;
        aux->prev = NULL;
        aux->next = NULL;
    }

    return aux;
}

/**
 * @brief Insere uma antena criada na lista ligada das antenas.
 * 
 * @param grafoHead Inicio da lista das antenas.
 * @param novo Antena que pretendemos inserir na lista.
 * @return Antena* Inicio da lista atualizada.
 */
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

/**
 * @brief Insere uma antena criada, por ordem, na lista ligada das antenas.
 * 
 * @param grafoHead Inicio da lista das antenas.
 * @param novo Antena que pretendemos inserir na lista.
 * @return Antena* Inicio da lista atualizada.
 */
Antena* InsereAntenaOrdenado(Antena* grafoHead, Antena* novo) {
    if (!novo) return grafoHead;

    // Se a lista estiver vazia ou o novo deve ser o primeiro
    if (!grafoHead ||
        (novo->dados.x < grafoHead->dados.x) ||
        (novo->dados.x == grafoHead->dados.x && novo->dados.y < grafoHead->dados.y)) {
        novo->next = grafoHead;
        novo->prev = NULL;
        if (grafoHead) grafoHead->prev = novo;
        return novo;
    }

    Antena* aux = grafoHead;
    while (aux->next &&
          ((aux->next->dados.x < novo->dados.x) ||
           (aux->next->dados.x == novo->dados.x && aux->next->dados.y < novo->dados.y))) {
        aux = aux->next;
    }

    // Inserir novo após 'aux'
    novo->next = aux->next;
    novo->prev = aux;
    if (aux->next) aux->next->prev = novo;
    aux->next = novo;

    return grafoHead;
}

/**
 * @brief Remove uma antena (a sua lista de adjacencias e de efeitos nefastos) do grafo.
 * 
 * @param grafoHead Inicio da lista das antenas.
 * @param alvo Antena que pretendemos remover.
 * @return Antena* Inicio da lista atualizada.
 */
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

/**
 * @brief Encontra uma antena presente no grafo.
 * 
 * @param grafoHead Inicio da lista das antenas.
 * @param x Coordenada x da antena pretendida.
 * @param y Coordenada y da antena pretendida.
 * @return Antena* Se encontrou, devolve a antena, caso contrario, devolve NULL.
 */
Antena* EncontraAntena(Antena* grafoHead, int x, int y) {
    Antena* aux = grafoHead;
    while (aux) {
        if (aux->dados.x == x && aux->dados.y == y) return aux;

        aux = aux->next;
    }

    return NULL;
}

/**
 * @brief Destroi todo o grafo
 * 
 * @param grafoHead Inicio da lista das antenas.
 * @return Antena* Inicio vazio da lista das antenas.
 */
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

/**
 * @brief Cria uma nova adjunção com os dados passados por parametros.
 * 
 * @param valores Dados da adjacência.
 * @param original Antena que gerou a adjacência.
 * @return Adj* Nova adjacência criada.
 */
Adj* CriaAdj(DadosAntena valores, Antena* original) {
    Adj* aux = (Adj*)malloc(sizeof(Adj));

    // se conseguiu alocar memoria
    if (aux) {
        aux->dados = valores;
        aux->original = original;

        aux->prev = NULL;
        aux->next = NULL;
    }

    return aux;
}

/**
 * @brief Insere uma nova adjacência na lista das adjacências de uma antena.
 * 
 * @param adjHead Inicio da lista de adjacências de uma antena.
 * @param novo Nova adjacência a ser inserida.
 * @return Adj* Inicio da lista de adjacências atualizada.
 */
Adj* InsereAdj(Adj* adjHead, Adj* novo) {
    // se não existir uma nova adjacência, não ha nada a inserir
    if (!novo) return adjHead;

    // se não existir uma lista, a nova adj é a primeira
    if (!adjHead) {
        adjHead = novo;
        return adjHead;
    }

    // percorrer a lista até ao fim
    Adj* aux = adjHead;
    while (aux->next) {
        aux = aux->next;
    }

    // introduzir no fim
    aux->next = novo;
    novo->prev = aux;

    return adjHead;
}

/**
 * @brief Insere uma nova adjacência, ordenada,  na lista das adjacências de uma antena.
 * 
 * @param adjHead Inicio da lista de adjacências de uma antena.
 * @param novo Nova adjacência a ser inserida.
 * @return Adj* Inicio da lista de adjacências atualizada.
 */
Adj* InsereAdjOrdenado(Adj* adjHead, Adj* novo) {
    if (!novo) return adjHead;

    // Se a lista estiver vazia ou o novo deve ser o primeiro
    if (!adjHead ||
        (novo->dados.x < adjHead->dados.x) ||
        (novo->dados.x == adjHead->dados.x && novo->dados.y < adjHead->dados.y)) {
        novo->next = adjHead;
        novo->prev = NULL;
        if (adjHead) adjHead->prev = novo;
        return novo;
    }

    Adj* aux = adjHead;
    while (aux->next &&
          ((aux->next->dados.x < novo->dados.x) ||
           (aux->next->dados.x == novo->dados.x && aux->next->dados.y < novo->dados.y))) {
        aux = aux->next;
    }

    novo->next = aux->next;
    novo->prev = aux;
    if (aux->next) aux->next->prev = novo;
    aux->next = novo;

    return adjHead;
}

/**
 * @brief Remove uma adjacência de uma lista.
 * 
 * @param adjHead Inicio da lista de adjacências de uma antena.
 * @param alvo Adjacência a remover.
 * @return Adj* Inicio da lista de adjacências atualizada.
 */
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

/**
 * @brief Encontra uma adjunção presente na lista de uma antena.
 * 
 * @param adjHead Inicio da lista de adjacências de uma antena.
 * @param x Coordenada x da antena a encontar.
 * @param y Coordenada y da antena a encontar.
 * @return Adj* Adjunção encontrada (se não encontrou, devolve NULL).
 */
Adj* EncontraAdj(Adj* adjHead, int x, int y) {
    Adj* aux = adjHead;
    while (aux) {
        if (aux->dados.x == x && aux->dados.y == y) return aux;

        aux = aux->next;
    }

    return NULL;
}

/**
 * @brief Destroi a lista de adjacências de uma antena.
 * 
 * @param adjHead Inicio da lista de adjacências de uma antena.
 * @return Adj* Inicio da lista de adjacências vazia.
 */
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

/**
 * @brief Verifica se duas antenas são adjacentes.
 * 
 * @param a Primeira antena para comparar a existência de adjacência.
 * @param b Segunda antena para comparar a existência de adjacência.
 * @return true Se causa adjacência.
 * @return false Se não causa adjacência.
 */
bool CausaAdj(Antena* a, Antena* b) {
    // são a mesma antena
    if (a == b) return false;

    // se não tiverem a mesma frequencia, não ha adj
    if (a->dados.freq != b->dados.freq) return false;

    // valor absoluto
    int difX = abs(a->dados.x - b->dados.x);
    int difY = abs(a->dados.y - b->dados.y);
    
    // verificar se a distância causa adjacência
    if (difX + difY > DIS_NEF) return false; 

    return true;
}

/**
 * @brief Gera a lista de adjacências para todas as antenas.
 * 
 * @param grafoHead Inicio da lista das antenas.
 * @return true Caso gere a lista com sucesso.
 * @return false Caso não exista lista.
 */
bool GeraAdj(Antena* grafoHead) {
    if (!grafoHead) return false;

    Antena* atual = grafoHead;
    while (atual) {
        Antena* comp = grafoHead;
        while (comp) {
            if (CausaAdj(atual, comp) && !EncontraAdj(atual->adjHead, comp->dados.x, comp->dados.y)) {
                Adj* aux = CriaAdj(comp->dados, comp);
                atual->adjHead = InsereAdjOrdenado(atual->adjHead, aux);
            }

            comp = comp->next;
        }

        atual = atual->next;
    }

    return true;
}

/**
 * @brief Remove uma antena das listas de adjacências das outras antenas.
 * 
 * @param grafoHead Inicio da lista das antenas.
 * @param alvo Antena a remover.
 * @return true Se conseguiu remover com sucesso.
 * @return false Se não existe grafo ou lista de adjacências da antena pretendida.
 */
bool RemoveOutrasAdj(Antena* grafoHead, Antena* alvo) {
    if (!grafoHead || !alvo) return false;

    Antena* antAux = grafoHead;
    while (antAux) {
        Adj* adjAux = antAux->adjHead;
        while (adjAux) {
            Adj* nextAdj = adjAux->next;
            if (adjAux->original == alvo) {
                antAux->adjHead = RemoveAdj(antAux->adjHead, adjAux);
            }
            adjAux = nextAdj;
        }
        antAux = antAux->next;
    }

    return true;
}

#pragma endregion
