/**
 * @file menus.c
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief Menu functions for the project.
 * @version 0.1
 * @date 18-05-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "includes.h"

/**
 * @brief Menu displayed to the user before the main program starts.
 * 
 * @return int Option selected by the user.
 */
int PreMenu() {
    int option;
    bool done = false;

    while (!done) {
        ClearTerminal();
        printf("Choose an option:\n\n");

        printf("1 - Create a new matrix\n");
        printf("2 - Load the graph from a binary file\n");
        printf("3 - Load the matrix from a text file\n");
        printf("0 - Exit\n\n");

        printf("option: ");
        scanf("%d", &option);
        printf("\n");

        if (option >= 0 && option <= 3) done = true;
        else {
            printf("invalid option!\n");
            Pause();
        }
    }

    return option;
}

/**
 * @brief Menu displayed to the user with the main operations.
 * 
 * @return int Option selected by the user.
 */
int MainMenu() {
    int option;
    bool done = false;

    while (!done) {
        ClearTerminal();
        printf("Choose an option:\n\n");

        printf(" 1 - Add antenna\n");
        printf(" 2 - Edit antenna\n");
        printf(" 3 - Remove antenna\n\n");

        printf(" 4 - Show matrix without adverse effects\n");
        printf(" 5 - Show matrix with adverse effects\n\n");

        printf(" 6 - Show list of all antennas\n");
        printf(" 7 - Show adjacency list for an antenna\n\n");

        printf(" 8 - Show list of all adverse effects\n");
        printf(" 9 - Show list of adverse effects for an antenna\n\n");

        printf("10 - Breadth-first search from an antenna\n");
        printf("11 - Depth-first search from an antenna\n\n");
        
        printf("12 - Save the graph to a binary file\n");
        printf("13 - Save the matrix to a text file\n\n");

        printf(" 0 - Exit\n\n");

        printf("option: ");
        scanf("%d", &option);
        printf("\n");

        if (option >= 0 && option <= 13) done = true;
        else {
            printf("invalid option!\n");
            Pause();
        }
    }

    return option;
}
