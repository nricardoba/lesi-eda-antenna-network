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

#pragma region Largura

/**
 * @brief Função que adiciona um vertice no fim da fila.
 * 
 * @param tail Apontador para o final da fila.
 * @param atual Apontador para a antena conectada ao vertice.
 * @return VerticeQueue* Ultimo vertice da fila atualizado.
 */
VerticeQueue* QueuePush(VerticeQueue* tail, Antena* atual) {
    VerticeQueue* novo = (VerticeQueue*)malloc(sizeof(VerticeQueue));
    if (!novo) return tail;

    novo->antena = atual;
    novo->next = NULL;

    if (tail) {
        tail->next = novo;
    }

    return novo;
}

/**
 * @brief Função que remove um vertice do inicio da fila.
 * 
 * @param head Apontador para o inicio da fila.
 * @return Antena* Antena que vamos manipular a seguir.
 */
Antena* QueuePop(VerticeQueue** head) {
    if (!*head) return NULL;

    Antena* aux = (*head)->antena;

    VerticeQueue* temp = *head;
    *head = (*head)->next;
    free(temp);

    return aux;
}

/**
 * @brief Função que utiliza a procura em largura para, a partir de um vertice, listar todos os vertices encontrados.
 * 
 * @param grafoHead Inicio da lista das antenas.
 * @param inicio Antena em que pretendemos iniciar a procura.
 * @return true Se consegui executar a procura em largura com sucesso.
 * @return false Se não exite grafo ou antena inicial.
 */
bool VisitaAdjBFS(Antena* grafoHead, Antena* inicio) {
    if (!grafoHead || !inicio) return false;

    ResetVisitados(grafoHead);

    VerticeQueue* queueHead = NULL;
    VerticeQueue* queueTail = NULL;

    queueTail = QueuePush(queueTail, inicio);
    queueHead = queueTail;
    inicio->visitado = 1;

    printf("Antenas alcançadas em largura por camada:\n");

    int camada = 0;
    int nodesNaCamada = 1;
    int nodesProximaCamada = 0;

    printf("\ncamada %d:\n", camada);

    while (queueHead) {
        Antena* atual = QueuePop(&queueHead);
        if (!queueHead) queueTail = NULL; // fila vazia

        printf("  (%c) x: %d, y: %d\n", atual->dados.freq, atual->dados.x, atual->dados.y);

        Adj* adj = atual->adjHead;
        while (adj) {
            if (adj->original && !adj->original->visitado) {
                queueTail = QueuePush(queueTail, adj->original);

                if (!queueHead) queueHead = queueTail;
                adj->original->visitado = 1;

                nodesProximaCamada++;
            }

            adj = adj->next;
        }

        nodesNaCamada--;
        if (nodesNaCamada == 0 && queueHead) {
            camada++;
            printf("\ncamada %d:\n", camada);
            nodesNaCamada = nodesProximaCamada;
            nodesProximaCamada = 0;
        }
    }

    return true;
}

/**
 * @brief Função que pede as coordenadas de uma antena e executa a procura em largura.
 * 
 * @param grafoHead Inicio da lista das antenas.
 * @return true Se conseguiu executar a procura com a antena pretendida.
 * @return false Se não existe antena com as coordenadas pretendidas ou não executou a procura.
 */
bool PerguntaVisitaBFS(Antena* grafoHead) {
    Coordenadas coorTemp = PedeCoordenadas("antena para começar a percorrer em largura:");

    Antena* aux = EncontraAntena(grafoHead, coorTemp.x, coorTemp.y);
    if (!aux) {
        printf("não existe essa antena!\n");
        return false;
    }

    if (!VisitaAdjBFS(grafoHead, aux))
        return false;

    return true;
}

#pragma endregion
#pragma region Profundidade

/**
 * @brief Função que adiciona um vertice no inicio da pilha.
 * 
 * @param head Apontador para o inicio da pilha.
 * @param atual Apontador para a antena conectada ao vertice.
 * @return VerticeStack* Inicio da pilha atualizado.
 */
VerticeStack* StackPush(VerticeStack* head, Antena* atual) {
    VerticeStack* novo = (VerticeStack*)malloc(sizeof(VerticeStack));
    if (!novo) return head;

    novo->antena = atual;
    novo->next = head;

    return novo;
}

/**
 * @brief Função que remove um vertice no inicio da pilha.
 * 
 * @param head Apontador para o inicio da pilha.
 * @return Antena* Antena que vamos manipular a seguir.
 */
Antena* StackPop(VerticeStack** head) {
    if (!*head) return NULL;

    Antena* aux = (*head)->antena;

    VerticeStack* temp = *head;
    *head = (*head)->next;
    free(temp);

    return aux;
}

/**
 * @brief Função que utiliza a procura em profundidade para, a partir de um vertice, listar todos os vertices encontrados.
 * 
 * @param grafoHead Inicio da lista das antenas.
 * @param inicio Antena em que pretendemos iniciar a procura.
 * @return true Se consegui executar a procura em profundidade com sucesso.
 * @return false Se não exite grafo ou antena inicial.
 */
bool VisitaAdjDFS(Antena* grafoHead, Antena* inicio) {
    if (!grafoHead || !inicio) return false;

    ResetVisitados(grafoHead);

    VerticeStack* stackHead = NULL;

    // coloca a antena inicial na stack
    stackHead = StackPush(stackHead, inicio);
    inicio->visitado = 1;

    printf("Antenas alcançadas em profundidade:\n");

    while (stackHead) {
        Antena* atual = StackPop(&stackHead);

        printf("  (%c) x: %d, y: %d\n", atual->dados.freq, atual->dados.x, atual->dados.y);

        Adj* adj = atual->adjHead;
        while (adj) {
            if (adj->original && !adj->original->visitado) {
                stackHead = StackPush(stackHead, adj->original);
                adj->original->visitado = 1;
            }

            adj = adj->next;
        }
    }

    return true;
}

/**
 * @brief Função que pede as coordenadas de uma antena e executa a procura em profundidade.
 * 
 * @param grafoHead Inicio da lista das antenas.
 * @return true Se conseguiu executar a procura com a antena pretendida.
 * @return false Se não existe antena com as coordenadas pretendidas ou não executou a procura.
 */
bool PerguntaVisitaDFS(Antena* grafoHead) {
    Coordenadas coorTemp = PedeCoordenadas("antena para começar a percorrer em profundidade:");

    Antena* aux = EncontraAntena(grafoHead, coorTemp.x, coorTemp.y);
    if (!aux) {
        printf("não existe essa antena!\n");
        return false;
    }

    if (!VisitaAdjDFS(grafoHead, aux))
        return false;

    return true;
}

#pragma endregion

/**
 * @brief Função que para todas as antenas coloca a variavel "visitado" a zero.
 * 
 * @param grafoHead Inicio da lista das antenas.
 * @return true Se conseguiu colocar tudo a zero.
 * @return false Se não existe grafo
 */
bool ResetVisitados(Antena* grafoHead) {
    if (!grafoHead) return false;

    Antena* aux = grafoHead;
    while (aux) {
        aux->visitado = 0;
        aux = aux->next;
    }

    return true;
}
