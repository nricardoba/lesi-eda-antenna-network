/**
 * @file termio.c
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief File that handles the project's terminal input and output functions.
 * @version 0.1
 * @date 18-05-2025
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "includes.h"

#pragma region Antennas

/**
 * @brief Prompts for an antenna's coordinates and, if possible, creates and
 * inserts it.
 *
 * @param graphHead Head of the antenna list.
 * @param matrix Matrix data.
 * @return Antenna* Head of the updated list.
 */
Antenna *CreateInsertAntenna(Antenna *graphHead, MatrixData matrix) {
    Coordinates tempCoordinates = PromptCoordinates("Coordinates:\n");

    if (FindAntenna(graphHead, tempCoordinates.x, tempCoordinates.y) ||
        !FitsInMatrix(matrix, tempCoordinates.x, tempCoordinates.y)) {
        printf("Invalid coordinates!\n");
        return graphHead;
    }

    AntennaData tempData;
    tempData.x = tempCoordinates.x;
    tempData.y = tempCoordinates.y;

    printf("Frequency: ");
    ClearInputBuffer();
    scanf("%c", &tempData.freq);

    if (!IsValidAntennaChar(tempData.freq)) {
        printf("Invalid frequency!\n");
        return graphHead;
    }

    Antenna *aux = CreateAntenna(tempData);
    graphHead = InsertAntennaSorted(graphHead, aux);

    return graphHead;
}

/**
 * @brief Prompts for an antenna's coordinates and, if possible, removes it.
 *
 * @param graphHead Head of the antenna list.
 * @return Antenna* Head of the updated list.
 */
Antenna *PromptRemoveAntenna(Antenna *graphHead) {
    if (!graphHead) {
        printf("No antenna list exists!\n");
        return NULL;
    }

    Coordinates tempCoordinates =
        PromptCoordinates("Which antenna do you want to remove?\n");
    Antenna *aux = FindAntenna(graphHead, tempCoordinates.x, tempCoordinates.y);

    if (!aux) {
        printf("No antenna exists at those coordinates!\n");
        return graphHead;
    }

    RemoveOtherAdjacencies(graphHead, aux);
    RemoveOtherAdverseEffects(graphHead, aux);
    graphHead = RemoveAntenna(graphHead, aux);

    printf("Antenna removed successfully!\n");

    return graphHead;
}

/**
 * @brief Updates an antenna's information, if possible.
 *
 * @param graphHead Head of the antenna list.
 * @param matrix Matrix data.
 * @return Antenna* Head of the updated list.
 */
Antenna *EditAntenna(Antenna *graphHead, MatrixData matrix) {
    if (!graphHead) {
        printf("No antenna list exists!\n");
        return NULL;
    }

    Coordinates tempCoordinates =
        PromptCoordinates("Which antenna do you want to edit?");
    Antenna *aux = FindAntenna(graphHead, tempCoordinates.x, tempCoordinates.y);

    if (!aux) {
        printf("No antenna exists at those coordinates!\n");
        return graphHead;
    }

    tempCoordinates = PromptCoordinates("New antenna data:");
    if (!FitsInMatrix(matrix, tempCoordinates.x, tempCoordinates.y) ||
        FindAntenna(graphHead, tempCoordinates.x, tempCoordinates.y)) {
        printf("Invalid coordinates!\n");
        return graphHead;
    }

    char freqTemp;
    printf("Frequency: ");
    ClearInputBuffer();
    scanf("%c", &freqTemp);
    printf("\n");

    if (!IsValidAntennaChar(freqTemp)) {
        printf("Invalid frequency!\n");
        return graphHead;
    }

    RemoveOtherAdjacencies(graphHead, aux);
    RemoveOtherAdverseEffects(graphHead, aux);
    aux->adjHead = DestroyAdjacencies(aux->adjHead);
    aux->effectHead = DestroyAdverseEffects(aux->effectHead);

    // assign new values
    aux->data.x = tempCoordinates.x;
    aux->data.y = tempCoordinates.y;
    aux->data.freq = freqTemp;

    GenerateAdjacencies(graphHead);
    GenerateAdverseEffects(graphHead, matrix);

    printf("Data updated successfully!\n");

    return graphHead;
}

/**
 * @brief Displays information about all antennas in the graph.
 *
 * @param graphHead Head of the antenna list.
 * @return true If at least one antenna exists.
 * @return false If the graph does not exist.
 */
bool ShowAntennaList(Antenna *graphHead) {
    // there is nothing to display
    if (!graphHead)
        return false;

    Antenna *aux = graphHead;
    int count = 1;

    while (aux) {
        printf("[%d]: %c --> x: %d, y: %d\n", count++, aux->data.freq,
               aux->data.x, aux->data.y);
        aux = aux->next;
    }

    return true;
}

/**
 * @brief Displays the matrix in the terminal without adverse effects.
 *
 * @param graphHead Head of the antenna list.
 * @param matrix Matrix data.
 * @return true If the matrix was displayed successfully.
 * @return false If the matrix data is invalid.
 */
bool ShowAntennaMatrix(Antenna *graphHead, MatrixData matrix) {
    if (matrix.rows <= 0 || matrix.columns <= 0)
        return false;

    // display the column numbers
    printf("  ");
    for (int n = 1; n <= matrix.columns; n++) {
        if (n < 10)
            printf("  %d", n);
        else if (n >= 10 && n < 100)
            printf(" %d", n);
        else
            printf("  ?");
    }
    printf("\n");

    for (int i = 1; i <= matrix.rows; i++) {

        if (i < 10)
            printf(" %d", i);
        else if (i >= 10 && i < 100)
            printf("%d", i);
        else
            printf(" ?");

        for (int j = 1; j <= matrix.columns; j++) {
            Antenna *aux = FindAntenna(graphHead, i, j);

            char temp = EMPTY;
            if (aux)
                temp = aux->data.freq;
            printf("  %c", temp);
        }
        printf("\n");
    }
    puts("\n");

    return true;
}

#pragma endregion
#pragma region Adjacencies

/**
 * @brief Displays an antenna's adjacency list.
 *
 * @param target Antenna whose adjacency list is to be displayed.
 * @return true If the list was displayed successfully.
 * @return false If the graph or adjacency list does not exist.
 */
bool ShowAdjacencyList(Antenna *target) {
    if (!target || !target->adjHead)
        return false;

    Adjacency *aux = target->adjHead;
    int count = 1;

    printf("All adjacencies of (%c) --> x: %d, y: %d\n", target->data.freq,
           target->data.x, target->data.y);
    while (aux) {
        printf("  [%d] %c --> x: %d, y: %d\n", count++, aux->data.freq,
               aux->data.x, aux->data.y);
        aux = aux->next;
    }

    return true;
}

/**
 * @brief Prompts for an antenna's information and displays its adjacencies in
 * the terminal.
 *
 * @param graphHead Head of the antenna list.
 * @return true If the adjacencies were displayed successfully.
 * @return false If the adjacencies could not be displayed.
 */
bool PromptShowAdjacencies(Antenna *graphHead) {
    if (!graphHead)
        return false;

    Coordinates tempCoordinates = PromptCoordinates(
        "Which antenna's adjacencies do you want to display?");
    Antenna *aux = FindAntenna(graphHead, tempCoordinates.x, tempCoordinates.y);

    if (!aux) {
        printf("No antenna exists at those coordinates!\n");
        return false;
    }

    if (!ShowAdjacencyList(aux)) {
        printf("That antenna has no adjacencies!\n");
        return false;
    }

    return true;
}

#pragma endregion
#pragma region Adverse Effects

/**
 * @brief Displays the adverse effect list of the selected antenna.
 *
 * @param target Antenna whose adverse effects are to be displayed.
 * @return true If the list was displayed successfully.
 * @return false If the graph or the selected antenna's adverse effect list does
 * not exist.
 */
bool ShowAdverseEffectList(Antenna *target) {
    if (!target || !target->effectHead)
        return false;

    AdverseEffect *aux = target->effectHead;
    int count = 1;

    printf("All adverse effects of (%c) --> x: %d, y: %d\n", target->data.freq,
           target->data.x, target->data.y);
    while (aux) {
        printf("  [%d] %c --> x: %d, y: %d\n", count++, ADVERSE_EFFECT,
               aux->data.x, aux->data.y);
        aux = aux->next;
    }

    return true;
}

/**
 * @brief Prompts for an antenna's information and displays its adverse effect
 * list in the terminal.
 *
 * @param graphHead Head of the antenna list.
 * @return true If the list was displayed successfully.
 * @return false If the list could not be displayed.
 */
bool PromptShowAdverseEffects(Antenna *graphHead) {
    if (!graphHead)
        return false;

    Coordinates tempCoordinates = PromptCoordinates(
        "Which antenna's adverse effects do you want to display?");
    Antenna *aux = FindAntenna(graphHead, tempCoordinates.x, tempCoordinates.y);

    if (!aux) {
        printf("No antenna exists at those coordinates!\n");
        return false;
    }

    if (!ShowAdverseEffectList(aux)) {
        printf("That antenna has no adverse effects!\n");
        return false;
    }

    return true;
}

/**
 * @brief Displays the adverse effect lists of all antennas in the graph.
 *
 * @param graphHead Head of the antenna list.
 * @return true If the lists were displayed successfully.
 * @return false If the graph does not exist.
 */
bool ShowAllAdverseEffects(Antenna *graphHead) {
    if (!graphHead)
        return false;

    Antenna *aux = graphHead;
    while (aux) {
        ShowAdverseEffectList(aux);
        printf("\n");

        aux = aux->next;
    }

    return true;
}

/**
 * @brief Displays the complete matrix in the terminal.
 *
 * @param graphHead Head of the antenna list.
 * @param matrix Matrix data.
 * @return true If the matrix was displayed successfully.
 * @return false If the matrix data is invalid.
 */
bool ShowAdverseEffectMatrix(Antenna *graphHead, MatrixData matrix) {
    if (matrix.rows <= 0 || matrix.columns <= 0)
        return false;

    // display the column numbers
    printf("  ");
    for (int n = 1; n <= matrix.columns; n++) {
        if (n < 10)
            printf("  %d", n);
        else if (n >= 10 && n < 100)
            printf(" %d", n);
        else
            printf("  ?");
    }
    printf("\n");

    for (int i = 1; i <= matrix.rows; i++) {

        if (i < 10)
            printf(" %d", i);
        else if (i >= 10 && i < 100)
            printf("%d", i);
        else
            printf(" ?");

        for (int j = 1; j <= matrix.columns; j++) {
            Antenna *aux = FindAntenna(graphHead, i, j);
            bool hasEffect = HasAdverseEffect(graphHead, i, j);

            char temp = EMPTY;
            if (aux && hasEffect)
                temp = OVERLAP;
            else if (aux)
                temp = aux->data.freq;
            else if (hasEffect)
                temp = ADVERSE_EFFECT;
            printf("  %c", temp);
        }
        printf("\n");
    }
    puts("\n");

    return true;
}

#pragma endregion
#pragma region Matrix and File

/**
 * @brief Reads a matrix from a text file.
 *
 * @param filename File name.
 * @param graphHead Head of the antenna list.
 * @param matrix Matrix data.
 * @return Antenna* Head of the updated list.
 */
Antenna *ReadMatrixFile(char *filename, Antenna *graphHead,
                        MatrixData *matrix) {
    FILE *fp = fopen(filename, "rt");
    // if the file cannot be opened, return the list unchanged
    if (!fp)
        return graphHead;

    // destroy the list to create a new one
    graphHead = DestroyAntennas(graphHead);

    matrix->rows = 0;
    matrix->columns = 0;
    int currentColumns = 0;
    char tempChar;

    // may be needed
    // ClearInputBuffer();

    while ((tempChar = fgetc(fp)) != EOF) {
        if (tempChar == END_LINE) {
            if (matrix->rows < MAX_MATRIX)
                matrix->rows++;

            if (matrix->columns < currentColumns)
                matrix->columns = currentColumns;

            currentColumns = 0;
        } else if (currentColumns < MAX_MATRIX) {
            currentColumns++;

            // checking for an antenna at the current coordinates should not be
            // necessary, because a new list is being created
            if (IsValidAntennaChar(tempChar)) {
                AntennaData tempData;
                tempData.x = matrix->rows + 1;
                tempData.y = currentColumns;
                tempData.freq = tempChar;

                Antenna *aux = CreateAntenna(tempData);
                graphHead = InsertAntennaSorted(graphHead, aux);
            }
        }
    }

    // check whether the last row was not counted (if the file does not end with
    // '\n')
    if (currentColumns > 0 && matrix->rows < MAX_MATRIX) {
        matrix->rows++;

        if (matrix->columns < currentColumns)
            matrix->columns = currentColumns;
    }
    fclose(fp);

    return graphHead;
}

/**
 * @brief Reads graph data from a binary file.
 *
 * @param filename File name.
 * @param graphHead Head of the antenna list.
 * @param matrix Matrix data.
 * @return Antenna* Head of the updated list.
 */
Antenna *ReadAntennasBinary(char *filename, Antenna *graphHead,
                            MatrixData matrix) {
    FILE *fp = fopen(filename, "rb");
    if (!fp)
        return graphHead;

    graphHead = DestroyAntennas(graphHead);

    AntennaData tempData;
    while (fread(&tempData, sizeof(AntennaData), 1, fp) == 1) {
        if (FitsInMatrix(matrix, tempData.x, tempData.y)) {
            Antenna *aux = CreateAntenna(tempData);
            graphHead = InsertAntennaSorted(graphHead, aux);
        }
    }
    fclose(fp);

    return graphHead;
}

/**
 * @brief Saves the matrix and antennas to a text file.
 *
 * @param filename File name.
 * @param graphHead Head of the antenna list.
 * @param matrix Matrix data.
 * @return true If the data was saved successfully.
 * @return false If the data could not be saved.
 */
bool SaveMatrixFile(char *filename, Antenna *graphHead, MatrixData matrix) {
    if (!IsValidMatrix(matrix))
        return false;

    FILE *fp = fopen(filename, "wt");
    if (!fp)
        return false;

    for (int i = 1; i <= matrix.rows; i++) {
        for (int j = 1; j <= matrix.columns; j++) {
            Antenna *aux = FindAntenna(graphHead, i, j);

            char temp = EMPTY;
            if (aux)
                temp = aux->data.freq;
            fprintf(fp, "%c", temp);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);

    return true;
}

/**
 * @brief Saves graph data to a binary file.
 *
 * @param filename File name.
 * @param graphHead Head of the antenna list.
 * @return true If the data was saved successfully.
 * @return false If the data could not be saved.
 */
bool SaveAntennasBinary(char *filename, Antenna *graphHead) {
    if (!graphHead)
        return false;

    FILE *fp = fopen(filename, "wb");
    if (!fp)
        return false;

    Antenna *aux = graphHead;
    while (aux) {
        if (fwrite(&(aux->data), sizeof(AntennaData), 1, fp) != 1) {
            fclose(fp);
            return false;
        }
        aux = aux->next;
    }
    fclose(fp);

    return true;
}

/**
 * @brief Creates a matrix with dimensions chosen by the user.
 *
 * @param matrix Matrix data.
 * @return MatrixData Updated matrix.
 */
MatrixData CreateMatrix(MatrixData matrix) {
    MatrixData temp;
    printf("Rows: ");
    scanf("%d", &temp.rows);
    printf("Columns: ");
    scanf("%d", &temp.columns);

    if (!IsValidMatrix(temp)) {
        matrix.rows = 10;
        matrix.columns = 10;

        return matrix;
    }

    matrix = temp;
    return matrix;
}

/**
 * @brief Prompts the user for coordinates.
 *
 * @param message Message for the user.
 * @return Coordinates chosen by the user.
 */
Coordinates PromptCoordinates(char *message) {
    Coordinates aux;

    printf("%s\n", message);
    printf("x: ");
    scanf("%d", &aux.x);
    printf("y: ");
    scanf("%d", &aux.y);
    printf("\n");

    return aux;
}

#pragma endregion
