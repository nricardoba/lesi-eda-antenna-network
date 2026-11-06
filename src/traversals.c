/**
 * @file traversals.c
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief Graph traversal functions for the project.
 * @version 0.1
 * @date 18-05-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "includes.h"

#pragma region BreadthFirst

/**
 * @brief Adds a vertex to the end of the queue.
 * 
 * @param tail Pointer to the end of the queue.
 * @param current Pointer to the antenna connected to the vertex.
 * @return VertexQueue* Updated last vertex in the queue.
 */
VertexQueue* QueuePush(VertexQueue* tail, Antenna* current) {
    VertexQueue* newNode = (VertexQueue*)malloc(sizeof(VertexQueue));
    if (!newNode) return tail;

    newNode->antenna = current;
    newNode->next = NULL;

    if (tail) {
        tail->next = newNode;
    }

    return newNode;
}

/**
 * @brief Removes a vertex from the front of the queue.
 * 
 * @param head Pointer to the front of the queue.
 * @return Antenna* Next antenna to process.
 */
Antenna* QueuePop(VertexQueue** head) {
    if (!*head) return NULL;

    Antenna* aux = (*head)->antenna;

    VertexQueue* temp = *head;
    *head = (*head)->next;
    free(temp);

    return aux;
}

/**
 * @brief Uses breadth-first search to list all vertices reachable from a starting vertex.
 * 
 * @param graphHead Head of the antenna list.
 * @param start Antenna at which to start the search.
 * @return true If the breadth-first search completed successfully.
 * @return false If the graph or starting antenna does not exist.
 */
bool VisitAdjacenciesBFS(Antenna* graphHead, Antenna* start) {
    if (!graphHead || !start) return false;

    ResetVisited(graphHead);

    VertexQueue* queueHead = NULL;
    VertexQueue* queueTail = NULL;

    queueTail = QueuePush(queueTail, start);
    queueHead = queueTail;
    start->visited = 1;

    printf("Antennas reached by breadth-first search, grouped by layer:\n");

    int layer = 0;
    int nodesInLayer = 1;
    int nodesInNextLayer = 0;

    printf("\nlayer %d:\n", layer);

    while (queueHead) {
        Antenna* current = QueuePop(&queueHead);
        if (!queueHead) queueTail = NULL; // empty queue

        printf("  (%c) x: %d, y: %d\n", current->data.freq, current->data.x, current->data.y);

        Adjacency* adj = current->adjHead;
        while (adj) {
            if (adj->original && !adj->original->visited) {
                queueTail = QueuePush(queueTail, adj->original);

                if (!queueHead) queueHead = queueTail;
                adj->original->visited = 1;

                nodesInNextLayer++;
            }

            adj = adj->next;
        }

        nodesInLayer--;
        if (nodesInLayer == 0 && queueHead) {
            layer++;
            printf("\nlayer %d:\n", layer);
            nodesInLayer = nodesInNextLayer;
            nodesInNextLayer = 0;
        }
    }

    return true;
}

/**
 * @brief Prompts for an antenna's coordinates and performs a breadth-first search.
 * 
 * @param graphHead Head of the antenna list.
 * @return true If the search completed with the requested antenna.
 * @return false If no antenna has the requested coordinates or the search did not run.
 */
bool PromptVisitBFS(Antenna* graphHead) {
    Coordinates tempCoordinates = PromptCoordinates("antenna to start the breadth-first traversal:");

    Antenna* aux = FindAntenna(graphHead, tempCoordinates.x, tempCoordinates.y);
    if (!aux) {
        printf("that antenna does not exist!\n");
        return false;
    }

    if (!VisitAdjacenciesBFS(graphHead, aux))
        return false;

    return true;
}

#pragma endregion
#pragma region DepthFirst

/**
 * @brief Adds a vertex to the top of the stack.
 * 
 * @param head Pointer to the top of the stack.
 * @param current Pointer to the antenna connected to the vertex.
 * @return VertexStack* Updated top of the stack.
 */
VertexStack* StackPush(VertexStack* head, Antenna* current) {
    VertexStack* newNode = (VertexStack*)malloc(sizeof(VertexStack));
    if (!newNode) return head;

    newNode->antenna = current;
    newNode->next = head;

    return newNode;
}

/**
 * @brief Removes a vertex from the top of the stack.
 * 
 * @param head Pointer to the top of the stack.
 * @return Antenna* Next antenna to process.
 */
Antenna* StackPop(VertexStack** head) {
    if (!*head) return NULL;

    Antenna* aux = (*head)->antenna;

    VertexStack* temp = *head;
    *head = (*head)->next;
    free(temp);

    return aux;
}

/**
 * @brief Uses depth-first search to list all vertices reachable from a starting vertex.
 * 
 * @param graphHead Head of the antenna list.
 * @param start Antenna at which to start the search.
 * @return true If the depth-first search completed successfully.
 * @return false If the graph or starting antenna does not exist.
 */
bool VisitAdjacenciesDFS(Antenna* graphHead, Antenna* start) {
    if (!graphHead || !start) return false;

    ResetVisited(graphHead);

    VertexStack* stackHead = NULL;

    // place the starting antenna on the stack
    stackHead = StackPush(stackHead, start);
    start->visited = 1;

    printf("Antennas reached by depth-first search:\n");

    while (stackHead) {
        Antenna* current = StackPop(&stackHead);

        printf("  (%c) x: %d, y: %d\n", current->data.freq, current->data.x, current->data.y);

        Adjacency* adj = current->adjHead;
        while (adj) {
            if (adj->original && !adj->original->visited) {
                stackHead = StackPush(stackHead, adj->original);
                adj->original->visited = 1;
            }

            adj = adj->next;
        }
    }

    return true;
}

/**
 * @brief Prompts for an antenna's coordinates and performs a depth-first search.
 * 
 * @param graphHead Head of the antenna list.
 * @return true If the search completed with the requested antenna.
 * @return false If no antenna has the requested coordinates or the search did not run.
 */
bool PromptVisitDFS(Antenna* graphHead) {
    Coordinates tempCoordinates = PromptCoordinates("antenna to start the depth-first traversal:");

    Antenna* aux = FindAntenna(graphHead, tempCoordinates.x, tempCoordinates.y);
    if (!aux) {
        printf("that antenna does not exist!\n");
        return false;
    }

    if (!VisitAdjacenciesDFS(graphHead, aux))
        return false;

    return true;
}

#pragma endregion

/**
 * @brief Sets the "visited" variable to zero for all antennas.
 * 
 * @param graphHead Head of the antenna list.
 * @return true If all visited flags were set to zero.
 * @return false If the graph does not exist.
 */
bool ResetVisited(Antenna* graphHead) {
    if (!graphHead) return false;

    Antenna* aux = graphHead;
    while (aux) {
        aux->visited = 0;
        aux = aux->next;
    }

    return true;
}
