/**
 * @file func.h
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief Header file for func.c.
 * @version 0.1
 * @date 18-05-2025
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "includes.h"

// Matrix validation
bool FitsInMatrix(MatrixData matrix, int x, int y);
bool IsValidMatrix(MatrixData matrix);
bool IsValidAntennaChar(char character);
