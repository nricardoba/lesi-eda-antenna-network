/**
 * @file data.h
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief Project constants and data structure definitions.
 * @version 0.1
 * @date 30-03-2025
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "includes.h"

#define ADVERSE_EFFECT '#' // adverse effect
#define OVERLAP '@'        // antenna and adverse effect overlap
#define EMPTY '.'          // empty cell
#define SPACE ' '          // space character
#define END_LINE '\n'      // newline character

#define MAX_MATRIX 30             // maximum number of matrix rows and columns
#define ADVERSE_EFFECT_DISTANCE 5 // distance threshold for adverse effects

#pragma region Data Structures

/**
 * @brief Antenna data (coordinates and frequency).
 *
 */
typedef struct AntennaData {
    char freq;
    int x, y;
} AntennaData;

/**
 * @brief Matrix dimensions (rows and columns).
 *
 */
typedef struct MatrixData {
    int rows, columns;
} MatrixData;

/**
 * @brief Vertex coordinates (position in the matrix).
 *
 */
typedef struct Coordinates {
    int x, y;
} Coordinates;

#pragma endregion
#pragma region Antennas

/**
 * @brief Antenna list node with its adjacency and adverse-effect lists.
 *
 */
typedef struct Antenna {
    AntennaData data;
    int visited;
    struct Adjacency *adjHead;
    struct AdverseEffect *effectHead;
    struct Antenna *prev;
    struct Antenna *next;
} Antenna;

/**
 * @brief Adjacency list node for an antenna.
 *
 */
typedef struct Adjacency {
    AntennaData data;
    struct Antenna *original;
    struct Adjacency *prev;
    struct Adjacency *next;
} Adjacency;

/**
 * @brief Adverse-effect list node for an antenna.
 *
 */
typedef struct AdverseEffect {
    AntennaData data;
    struct Antenna *parent;
    struct AdverseEffect *next;
} AdverseEffect;

#pragma endregion
#pragma region Stack

/**
 * @brief Antenna stack node used for graph traversals.
 *
 */
typedef struct VertexStack {
    struct Antenna *antenna;
    struct VertexStack *next;
} VertexStack;

typedef struct VertexQueue {
    struct Antenna *antenna;
    struct VertexQueue *next;
} VertexQueue;

#pragma endregion
