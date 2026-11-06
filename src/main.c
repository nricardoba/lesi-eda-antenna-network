/**
 * @file main.c
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief Main program for managing the graph.
 *
 * GitHub repository: https://github.com/ricardobara/TPEDA2425.git
 *
 * @version 0.1
 * @date 18-05-2025
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "includes.h"

/**
 * @brief Initializes the graph and matrix and manages the program menus.
 *
 * @return int Exit status.
 */
int main() {
    // Initialize the graph
    Antenna *graphHead = NULL;

    // Initialize the matrix
    MatrixData matrix;
    matrix.rows = 0;
    matrix.columns = 0;

    // Determine when the program ends
    bool done = false;

#pragma region Pre Menu

    int option = PreMenu();

    ClearTerminal();
    switch (option) {
    case 1:
        // Create an empty matrix
        matrix = CreateMatrix(matrix);
        break;
    case 2:
        // Read the graph data from a binary file
        matrix = CreateMatrix(matrix);
        graphHead = ReadAntennasBinary("graph.bin", graphHead, matrix);

        // Generate the adjacency and adverse-effect lists
        GenerateAdjacencies(graphHead);
        GenerateAdverseEffects(graphHead, matrix);
        break;
    case 3:
        // Read the antenna and matrix data from the text file
        graphHead = ReadMatrixFile("antennas.txt", graphHead, &matrix);

        // Create a matrix if the loaded dimensions are invalid
        if (!IsValidMatrix(matrix)) {
            printf("Invalid matrix. Let's create one!\n");

            // Create an empty matrix
            matrix = CreateMatrix(matrix);
        }

        // Generate the adjacency and adverse-effect lists
        GenerateAdjacencies(graphHead);
        GenerateAdverseEffects(graphHead, matrix);

        break;
    default:
        done = true;
    }

#pragma endregion
#pragma region Main Menu

    if (!done) {
        while (!done) {
            option = MainMenu();
            ClearTerminal();

            switch (option) {
            case 1:
                // Create and insert an antenna and generate its adjacency and
                // adverse-effect lists
                graphHead = CreateInsertAntenna(graphHead, matrix);
                GenerateAdjacencies(graphHead);
                GenerateAdverseEffects(graphHead, matrix);
                break;
            case 2:
                // Edit an antenna's data
                graphHead = EditAntenna(graphHead, matrix);
                break;
            case 3:
                // Remove an antenna from the graph
                graphHead = PromptRemoveAntenna(graphHead);
                break;
            case 4:
                // Show the matrix with antennas only
                if (!ShowAntennaMatrix(graphHead, matrix))
                    printf("No matrix available!\n");
                break;
            case 5:
                // Show the complete matrix
                if (!ShowAdverseEffectMatrix(graphHead, matrix))
                    printf("No matrix available!\n");
                break;
            case 6:
                // Show the antenna list
                if (!ShowAntennaList(graphHead))
                    printf("No antenna list available!\n");
                break;
            case 7:
                // Show an antenna's adjacency list
                PromptShowAdjacencies(graphHead);
                break;
            case 8:
                // Show all adverse effects in the graph
                ShowAllAdverseEffects(graphHead);
                break;
            case 9:
                // Show an antenna's adverse effects
                PromptShowAdverseEffects(graphHead);
                break;
            case 10:
                // Show the antennas reached by breadth-first search
                PromptVisitBFS(graphHead);
                break;
            case 11:
                // Show the antennas reached by depth-first search
                PromptVisitDFS(graphHead);
                break;
            case 12:
                // Save the graph data to a binary file
                if (SaveAntennasBinary("graph.bin", graphHead))
                    printf("Data saved successfully!\n");
                else
                    printf("Could not save the data!\n");
                break;
            case 13:
                // Save the matrix with antennas only to a text file
                if (SaveMatrixFile("antennas.txt", graphHead, matrix))
                    printf("Data saved successfully!\n");
                else
                    printf("Could not save the data!\n");
                break;
            default:
                done = true;
            }
            if (!done)
                Pause();
        }
    }

#pragma endregion

    // Destroy the graph
    graphHead = DestroyAntennas(graphHead);
    printf("Program terminated!\n\n");

    return 0;
}
