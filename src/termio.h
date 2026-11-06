/**
 * @file termio.h
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief Header file for termio.c.
 * @version 0.1
 * @date 18-05-2025
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "includes.h"

Antenna *CreateInsertAntenna(Antenna *graphHead, MatrixData matrix);
Antenna *PromptRemoveAntenna(Antenna *graphHead);
Antenna *EditAntenna(Antenna *graphHead, MatrixData matrix);
bool ShowAntennaList(Antenna *graphHead);
bool ShowAntennaMatrix(Antenna *graphHead, MatrixData matrix);

bool ShowAdjacencyList(Antenna *target);
bool PromptShowAdjacencies(Antenna *graphHead);

bool ShowAdverseEffectList(Antenna *target);
bool PromptShowAdverseEffects(Antenna *graphHead);
bool ShowAllAdverseEffects(Antenna *graphHead);
bool ShowAdverseEffectMatrix(Antenna *graphHead, MatrixData matrix);

Antenna *ReadMatrixFile(char *filename, Antenna *graphHead, MatrixData *matrix);
Antenna *ReadAntennasBinary(char *filename, Antenna *graphHead,
                            MatrixData matrix);
bool SaveMatrixFile(char *filename, Antenna *graphHead, MatrixData matrix);
bool SaveAntennasBinary(char *filename, Antenna *graphHead);

MatrixData CreateMatrix(MatrixData matrix);
Coordinates PromptCoordinates(char *message);
