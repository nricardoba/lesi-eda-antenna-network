/**
 * @file adverse_effects.h
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief Header file for adverse_effects.c.
 * @version 0.1
 * @date 18-05-2025
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "includes.h"

AdverseEffect *CreateAdverseEffect(AntennaData values, Antenna *parent);
AdverseEffect *InsertAdverseEffect(AdverseEffect *effectHead,
                                   AdverseEffect *newNode);
AdverseEffect *InsertAdverseEffectSorted(AdverseEffect *effectHead,
                                         AdverseEffect *newNode);
AdverseEffect *RemoveAdverseEffect(AdverseEffect *effectHead,
                                   AdverseEffect *target);
AdverseEffect *FindAdverseEffect(AdverseEffect *effectHead, Antenna *parent,
                                 int x, int y);
bool CreateInsertAdverseEffects(Antenna *current, Antenna *comparison,
                                MatrixData matrix);
bool GenerateAdverseEffects(Antenna *graphHead, MatrixData matrix);
AdverseEffect *DestroyAdverseEffects(AdverseEffect *effectHead);

bool CauseAdverseEffect(Antenna *a, Antenna *b);
bool HasAdverseEffect(Antenna *graphHead, int x, int y);
bool RemoveOtherAdverseEffects(Antenna *graphHead, Antenna *target);
