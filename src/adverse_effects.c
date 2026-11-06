/**
 * @file adverse_effects.c
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief Adverse effect management functions for the project.
 * @version 0.1
 * @date 18-05-2025
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "includes.h"

/**
 * @brief Creates a new adverse effect with the supplied data.
 *
 * @param values Adverse effect data.
 * @param parent Antenna that generated the adverse effect.
 * @return AdverseEffect* Newly created adverse effect.
 */
AdverseEffect *CreateAdverseEffect(AntennaData values, Antenna *parent) {
    AdverseEffect *aux = (AdverseEffect *)malloc(sizeof(AdverseEffect));

    if (aux) {
        aux->data = values;
        aux->parent = parent;

        aux->next = NULL;
    }

    return aux;
}

/**
 * @brief Inserts a new adverse effect into an antenna's list.
 *
 * @param effectHead Head of an antenna's adverse effect list.
 * @param newNode New adverse effect to insert.
 * @return AdverseEffect* Head of the updated adverse effect list.
 */
AdverseEffect *InsertAdverseEffect(AdverseEffect *effectHead,
                                   AdverseEffect *newNode) {
    if (!newNode)
        return effectHead;

    if (!effectHead) {
        effectHead = newNode;
        return effectHead;
    }

    AdverseEffect *aux = effectHead;
    while (aux->next) {
        aux = aux->next;
    }

    aux->next = newNode;

    return effectHead;
}

/**
 * @brief Inserts a new adverse effect in sorted order into an antenna's list.
 *
 * @param effectHead Head of an antenna's adverse effect list.
 * @param newNode New adverse effect to insert.
 * @return AdverseEffect* Head of the updated adverse effect list.
 */
AdverseEffect *InsertAdverseEffectSorted(AdverseEffect *effectHead,
                                         AdverseEffect *newNode) {
    if (!newNode)
        return effectHead;

    // If the list is empty or the new node should be first
    if (!effectHead || (newNode->data.x < effectHead->data.x) ||
        (newNode->data.x == effectHead->data.x &&
         newNode->data.y < effectHead->data.y)) {
        newNode->next = effectHead;
        return newNode;
    }

    AdverseEffect *aux = effectHead;
    while (aux->next && ((aux->next->data.x < newNode->data.x) ||
                         (aux->next->data.x == newNode->data.x &&
                          aux->next->data.y < newNode->data.y))) {
        aux = aux->next;
    }

    newNode->next = aux->next;
    aux->next = newNode;

    return effectHead;
}

/**
 * @brief Removes an adverse effect from a list.
 *
 * @param effectHead Head of an antenna's adverse effect list.
 * @param target Adverse effect to remove.
 * @return AdverseEffect* Head of the updated adverse effect list.
 */
AdverseEffect *RemoveAdverseEffect(AdverseEffect *effectHead,
                                   AdverseEffect *target) {
    if (!effectHead || !target)
        return effectHead;

    if (effectHead == target) {
        effectHead = effectHead->next;
        free(target);
        return effectHead;
    }

    AdverseEffect *aux = effectHead;
    while (aux->next && aux->next != target) {
        aux = aux->next;
    }

    if (aux->next == target) {
        aux->next = target->next;
        free(target);
    }

    return effectHead;
}

/**
 * @brief Finds an adverse effect in an antenna's list.
 *
 * @param effectHead Head of an antenna's adverse effect list.
 * @param parent Antenna that generated the adverse effect.
 * @param x x-coordinate of the adverse effect to find.
 * @param y y-coordinate of the adverse effect to find.
 * @return AdverseEffect* The adverse effect if found, otherwise NULL.
 */
AdverseEffect *FindAdverseEffect(AdverseEffect *effectHead, Antenna *parent,
                                 int x, int y) {
    AdverseEffect *aux = effectHead;
    while (aux) {
        if (aux->parent == parent && aux->data.x == x && aux->data.y == y)
            return aux;

        aux = aux->next;
    }

    return NULL;
}

/**
 * @brief Calculates and inserts an adverse effect into an antenna's list.
 *
 * @param current Current antenna.
 * @param comparison Antenna to check for an adverse effect with the current
 * antenna.
 * @param matrix Matrix data.
 * @return true If creation and insertion succeeded.
 * @return false If the operation could not be completed.
 */
bool CreateInsertAdverseEffects(Antenna *current, Antenna *comparison,
                                MatrixData matrix) {
    if (!current || !comparison)
        return false;

    // if the two antennas do not cause an adverse effect, there is nothing to
    // record
    if (!CauseAdverseEffect(current, comparison))
        return false;

    for (int i = 0; i < 2; i++) {
        Antenna *a = NULL;
        Antenna *b = NULL;

        if (i == 0) {
            a = current;
            b = comparison;
        } else if (i == 1) {
            a = comparison;
            b = current;
        }

        int newX = a->data.x + (a->data.x - b->data.x);
        int newY = a->data.y + (a->data.y - b->data.y);

        if (!FindAdverseEffect(current->effectHead, comparison, newX, newY) &&
            FitsInMatrix(matrix, newX, newY)) {
            AntennaData tempData;
            tempData.freq = current->data.freq;
            tempData.x = newX;
            tempData.y = newY;

            AdverseEffect *aux = CreateAdverseEffect(tempData, comparison);
            current->effectHead =
                InsertAdverseEffectSorted(current->effectHead, aux);
        }
    }

    return true;
}

/**
 * @brief Generates the adverse effect list for every antenna.
 *
 * @param graphHead Head of the antenna list.
 * @param matrix Matrix data.
 * @return true If adverse effects were generated successfully.
 * @return false If the graph does not exist.
 */
bool GenerateAdverseEffects(Antenna *graphHead, MatrixData matrix) {
    if (!graphHead)
        return false;

    Antenna *current = graphHead;
    while (current) {
        Antenna *comparison = graphHead;
        while (comparison) {
            CreateInsertAdverseEffects(current, comparison, matrix);

            comparison = comparison->next;
        }

        current = current->next;
    }

    return true;
}

/**
 * @brief Destroys an antenna's adverse effect list.
 *
 * @param effectHead Head of an antenna's adverse effect list.
 * @return AdverseEffect* Head of the empty adverse effect list.
 */
AdverseEffect *DestroyAdverseEffects(AdverseEffect *effectHead) {
    if (!effectHead)
        return NULL;

    AdverseEffect *aux = NULL;
    while (effectHead) {
        aux = effectHead;
        effectHead = effectHead->next;
        free(aux);
    }

    return effectHead;
}

/**
 * @brief Checks whether two antennas cause an adverse effect.
 *
 * @param a First antenna to check for an adverse effect.
 * @param b Second antenna to check for an adverse effect.
 * @return true If the antennas cause an adverse effect.
 * @return false If the antennas do not cause an adverse effect.
 */
bool CauseAdverseEffect(Antenna *a, Antenna *b) {
    // they are the same antenna
    if (a == b)
        return false;

    // if they do not have the same frequency, there is no adverse effect
    if (a->data.freq != b->data.freq)
        return false;

    // absolute values
    int diffX = abs(a->data.x - b->data.x);
    int diffY = abs(a->data.y - b->data.y);

    if (diffX + diffY > ADVERSE_EFFECT_DISTANCE)
        return false;

    return true;
}

/**
 * @brief Checks whether the graph contains at least one adverse effect at the
 * desired coordinates.
 *
 * @param graphHead Head of the antenna list.
 * @param x x-coordinate of the adverse effect to find.
 * @param y y-coordinate of the adverse effect to find.
 * @return true If an adverse effect was found.
 * @return false If no adverse effect was found.
 */
bool HasAdverseEffect(Antenna *graphHead, int x, int y) {
    if (!graphHead)
        return false;

    Antenna *antennaAux = graphHead;
    while (antennaAux) {
        AdverseEffect *effectAux = antennaAux->effectHead;
        while (effectAux) {
            if (effectAux->data.x == x && effectAux->data.y == y)
                return true;

            effectAux = effectAux->next;
        }

        antennaAux = antennaAux->next;
    }

    return false;
}

/**
 * @brief Removes an adverse effect from the other antennas' lists.
 *
 * @param graphHead Head of the antenna list.
 * @param target Parent antenna of the adverse effect to remove.
 * @return true If removal succeeded.
 * @return false If the graph or target to remove does not exist.
 */
bool RemoveOtherAdverseEffects(Antenna *graphHead, Antenna *target) {
    if (!graphHead || !target)
        return false;

    Antenna *antennaAux = graphHead;
    while (antennaAux) {
        AdverseEffect *effectAux = antennaAux->effectHead;
        while (effectAux) {
            AdverseEffect *nextEffect = effectAux->next;
            if (effectAux->parent == target) {
                antennaAux->effectHead =
                    RemoveAdverseEffect(antennaAux->effectHead, effectAux);
            }
            effectAux = nextEffect;
        }

        antennaAux = antennaAux->next;
    }

    return true;
}
