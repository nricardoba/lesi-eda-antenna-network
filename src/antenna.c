/**
 * @file antenna.c
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief Antenna management functions for the project.
 * @version 0.1
 * @date 18-05-2025
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "includes.h"

#pragma region Antenna Functions

/**
 * @brief Creates a new antenna with the supplied data.
 *
 * @param values Antenna data.
 * @return Antenna* Pointer to the newly created antenna.
 */
Antenna *CreateAntenna(AntennaData values) {
    Antenna *aux = (Antenna *)malloc(sizeof(Antenna));

    // if memory was allocated successfully
    if (aux) {
        aux->data = values;

        aux->visited = 0;
        aux->adjHead = NULL;
        aux->effectHead = NULL;
        aux->prev = NULL;
        aux->next = NULL;
    }

    return aux;
}

/**
 * @brief Inserts a created antenna into the linked list of antennas.
 *
 * @param graphHead Head of the antenna list.
 * @param newNode Antenna to insert into the list.
 * @return Antenna* Head of the updated list.
 */
Antenna *InsertAntenna(Antenna *graphHead, Antenna *newNode) {
    // if there is no new antenna, there is nothing to insert
    if (!newNode)
        return graphHead;

    // if there is no list, the new antenna is the first
    if (!graphHead) {
        graphHead = newNode;
        return graphHead;
    }

    // traverse the list to the end
    Antenna *aux = graphHead;
    while (aux->next) {
        aux = aux->next;
    }

    // insert the new antenna at the end of the list
    aux->next = newNode;
    newNode->prev = aux;

    return graphHead;
}

/**
 * @brief Inserts a created antenna in sorted order into the linked list of
 * antennas.
 *
 * @param graphHead Head of the antenna list.
 * @param newNode Antenna to insert into the list.
 * @return Antenna* Head of the updated list.
 */
Antenna *InsertAntennaSorted(Antenna *graphHead, Antenna *newNode) {
    if (!newNode)
        return graphHead;

    // If the list is empty or the new node should be first
    if (!graphHead || (newNode->data.x < graphHead->data.x) ||
        (newNode->data.x == graphHead->data.x &&
         newNode->data.y < graphHead->data.y)) {
        newNode->next = graphHead;
        newNode->prev = NULL;
        if (graphHead)
            graphHead->prev = newNode;
        return newNode;
    }

    Antenna *aux = graphHead;
    while (aux->next && ((aux->next->data.x < newNode->data.x) ||
                         (aux->next->data.x == newNode->data.x &&
                          aux->next->data.y < newNode->data.y))) {
        aux = aux->next;
    }

    // Insert the new node after 'aux'
    newNode->next = aux->next;
    newNode->prev = aux;
    if (aux->next)
        aux->next->prev = newNode;
    aux->next = newNode;

    return graphHead;
}

/**
 * @brief Removes an antenna (including its adjacency and adverse effect lists)
 * from the graph.
 *
 * @param graphHead Head of the antenna list.
 * @param target Antenna to remove.
 * @return Antenna* Head of the updated list.
 */
Antenna *RemoveAntenna(Antenna *graphHead, Antenna *target) {
    // if there is no list, there is nothing to remove
    if (!graphHead || !target)
        return graphHead;

    // destroy the target's adjacency and adverse effect lists
    target->adjHead = DestroyAdjacencies(target->adjHead);
    target->effectHead = DestroyAdverseEffects(target->effectHead);

    // if the antenna to remove is the head of the list
    if (graphHead == target) {
        graphHead = graphHead->next;
        if (graphHead)
            graphHead->prev = NULL;
        free(target);

        return graphHead;
    }

    if (target->prev)
        target->prev->next = target->next;
    if (target->next)
        target->next->prev = target->prev;
    free(target);

    return graphHead;
}

/**
 * @brief Finds an antenna in the graph.
 *
 * @param graphHead Head of the antenna list.
 * @param x x-coordinate of the desired antenna.
 * @param y y-coordinate of the desired antenna.
 * @return Antenna* The antenna if found, otherwise NULL.
 */
Antenna *FindAntenna(Antenna *graphHead, int x, int y) {
    Antenna *aux = graphHead;
    while (aux) {
        if (aux->data.x == x && aux->data.y == y)
            return aux;

        aux = aux->next;
    }

    return NULL;
}

/**
 * @brief Destroys the entire graph.
 *
 * @param graphHead Head of the antenna list.
 * @return Antenna* Head of the empty antenna list.
 */
Antenna *DestroyAntennas(Antenna *graphHead) {
    if (!graphHead)
        return NULL;

    Antenna *aux = NULL;
    while (graphHead) {
        aux = graphHead;
        graphHead = graphHead->next;

        // destroy this vertex's adjacency list
        aux->adjHead = DestroyAdjacencies(aux->adjHead);

        // destroy this vertex's adverse effect list
        aux->effectHead = DestroyAdverseEffects(aux->effectHead);

        free(aux);
    }

    return graphHead;
}

#pragma endregion
#pragma region Adjacency Functions

/**
 * @brief Creates a new adjacency with the supplied data.
 *
 * @param values Adjacency data.
 * @param original Antenna that generated the adjacency.
 * @return Adjacency* Newly created adjacency.
 */
Adjacency *CreateAdjacency(AntennaData values, Antenna *original) {
    Adjacency *aux = (Adjacency *)malloc(sizeof(Adjacency));

    // if memory was allocated successfully
    if (aux) {
        aux->data = values;
        aux->original = original;

        aux->prev = NULL;
        aux->next = NULL;
    }

    return aux;
}

/**
 * @brief Inserts a new adjacency into an antenna's adjacency list.
 *
 * @param adjHead Head of an antenna's adjacency list.
 * @param newNode New adjacency to insert.
 * @return Adjacency* Head of the updated adjacency list.
 */
Adjacency *InsertAdjacency(Adjacency *adjHead, Adjacency *newNode) {
    // if there is no new adjacency, there is nothing to insert
    if (!newNode)
        return adjHead;

    // if there is no list, the new adjacency is the first
    if (!adjHead) {
        adjHead = newNode;
        return adjHead;
    }

    // traverse the list to the end
    Adjacency *aux = adjHead;
    while (aux->next) {
        aux = aux->next;
    }

    // insert at the end
    aux->next = newNode;
    newNode->prev = aux;

    return adjHead;
}

/**
 * @brief Inserts a new adjacency in sorted order into an antenna's adjacency
 * list.
 *
 * @param adjHead Head of an antenna's adjacency list.
 * @param newNode New adjacency to insert.
 * @return Adjacency* Head of the updated adjacency list.
 */
Adjacency *InsertAdjacencySorted(Adjacency *adjHead, Adjacency *newNode) {
    if (!newNode)
        return adjHead;

    // If the list is empty or the new node should be first
    if (!adjHead || (newNode->data.x < adjHead->data.x) ||
        (newNode->data.x == adjHead->data.x &&
         newNode->data.y < adjHead->data.y)) {
        newNode->next = adjHead;
        newNode->prev = NULL;
        if (adjHead)
            adjHead->prev = newNode;
        return newNode;
    }

    Adjacency *aux = adjHead;
    while (aux->next && ((aux->next->data.x < newNode->data.x) ||
                         (aux->next->data.x == newNode->data.x &&
                          aux->next->data.y < newNode->data.y))) {
        aux = aux->next;
    }

    newNode->next = aux->next;
    newNode->prev = aux;
    if (aux->next)
        aux->next->prev = newNode;
    aux->next = newNode;

    return adjHead;
}

/**
 * @brief Removes an adjacency from a list.
 *
 * @param adjHead Head of an antenna's adjacency list.
 * @param target Adjacency to remove.
 * @return Adjacency* Head of the updated adjacency list.
 */
Adjacency *RemoveAdjacency(Adjacency *adjHead, Adjacency *target) {
    if (!adjHead || !target)
        return adjHead;

    if (adjHead == target) {
        adjHead = adjHead->next;
        if (adjHead)
            adjHead->prev = NULL;
        free(target);

        return adjHead;
    }

    if (target->prev)
        target->prev->next = target->next;
    if (target->next)
        target->next->prev = target->prev;
    free(target);

    return adjHead;
}

/**
 * @brief Finds an adjacency in an antenna's list.
 *
 * @param adjHead Head of an antenna's adjacency list.
 * @param x x-coordinate of the antenna to find.
 * @param y y-coordinate of the antenna to find.
 * @return Adjacency* The adjacency if found, otherwise NULL.
 */
Adjacency *FindAdjacency(Adjacency *adjHead, int x, int y) {
    Adjacency *aux = adjHead;
    while (aux) {
        if (aux->data.x == x && aux->data.y == y)
            return aux;

        aux = aux->next;
    }

    return NULL;
}

/**
 * @brief Destroys an antenna's adjacency list.
 *
 * @param adjHead Head of an antenna's adjacency list.
 * @return Adjacency* Head of the empty adjacency list.
 */
Adjacency *DestroyAdjacencies(Adjacency *adjHead) {
    if (!adjHead)
        return NULL;

    Adjacency *aux = NULL;
    while (adjHead) {
        aux = adjHead;
        adjHead = adjHead->next;
        free(aux);
    }

    return adjHead;
}

/**
 * @brief Checks whether two antennas are adjacent.
 *
 * @param a First antenna to check for adjacency.
 * @param b Second antenna to check for adjacency.
 * @return true If the antennas are adjacent.
 * @return false If the antennas are not adjacent.
 */
bool AreAdjacent(Antenna *a, Antenna *b) {
    // they are the same antenna
    if (a == b)
        return false;

    // if they do not have the same frequency, they are not adjacent
    if (a->data.freq != b->data.freq)
        return false;

    // absolute values
    int diffX = abs(a->data.x - b->data.x);
    int diffY = abs(a->data.y - b->data.y);

    // check whether the distance makes the antennas adjacent
    if (diffX + diffY > ADVERSE_EFFECT_DISTANCE)
        return false;

    return true;
}

/**
 * @brief Generates the adjacency list for every antenna.
 *
 * @param graphHead Head of the antenna list.
 * @return true If the lists were generated successfully.
 * @return false If the antenna list does not exist.
 */
bool GenerateAdjacencies(Antenna *graphHead) {
    if (!graphHead)
        return false;

    Antenna *current = graphHead;
    while (current) {
        Antenna *comparison = graphHead;
        while (comparison) {
            if (AreAdjacent(current, comparison) &&
                !FindAdjacency(current->adjHead, comparison->data.x,
                               comparison->data.y)) {
                Adjacency *aux = CreateAdjacency(comparison->data, comparison);
                current->adjHead = InsertAdjacencySorted(current->adjHead, aux);
            }

            comparison = comparison->next;
        }

        current = current->next;
    }

    return true;
}

/**
 * @brief Removes an antenna from the other antennas' adjacency lists.
 *
 * @param graphHead Head of the antenna list.
 * @param target Antenna to remove.
 * @return true If removal succeeded.
 * @return false If the graph or the desired antenna's adjacency list does not
 * exist.
 */
bool RemoveOtherAdjacencies(Antenna *graphHead, Antenna *target) {
    if (!graphHead || !target)
        return false;

    Antenna *antennaAux = graphHead;
    while (antennaAux) {
        Adjacency *adjAux = antennaAux->adjHead;
        while (adjAux) {
            Adjacency *nextAdj = adjAux->next;
            if (adjAux->original == target) {
                antennaAux->adjHead =
                    RemoveAdjacency(antennaAux->adjHead, adjAux);
            }
            adjAux = nextAdj;
        }
        antennaAux = antennaAux->next;
    }

    return true;
}

#pragma endregion
