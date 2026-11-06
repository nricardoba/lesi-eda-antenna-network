/**
 * @file func.c
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief Helper functions for the project.
 * @version 0.1
 * @date 18-05-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "includes.h"

/**
 * @brief Checks whether a vertex fits in the matrix.
 * 
 * @param matrix Matrix data.
 * @param x The x-coordinate to check.
 * @param y The y-coordinate to check.
 * @return true If it fits in the matrix.
 * @return false If it does not fit in the matrix.
 */
bool FitsInMatrix(MatrixData matrix, int x, int y) {
    // neither coordinate can be <= 0
    if (x <= 0 || y <= 0) return false;

    // must fit within the number of matrix rows and columns
    if (x <= matrix.rows && y <= matrix.columns) return true;

    return false;
}

/**
 * @brief Checks whether the dimensions of a matrix are valid.
 * 
 * @param matrix Matrix data.
 * @return true If the dimensions are valid.
 * @return false If the dimensions are invalid.
 */
bool IsValidMatrix(MatrixData matrix) {
    // the number of rows and columns cannot be less than or equal to 0
    if (matrix.rows <= 0 || matrix.columns <= 0) return false;

    // the number of rows and columns cannot exceed the maximum
    if (matrix.rows <= MAX_MATRIX && matrix.columns <= MAX_MATRIX) return true;

    return false;
}

/**
 * @brief Checks whether a character can represent an antenna's frequency.
 * 
 * @param character Character to validate.
 * @return true If it can represent a frequency.
 * @return false If it is not valid.
 */
bool IsValidAntennaChar(char character) {
    if (character != EMPTY && character != ADVERSE_EFFECT && character != OVERLAP && character != SPACE && character != END_LINE) return true;
    return false;
}
