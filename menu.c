/**
 * Description : Contains the functions that handles the navigation of Mantis
 * Author/s : De Dios, Justin Marco C.
 *            Ocampo, Kysha Denise D.
 *  Section : S12A & S22A
 *  Last Modified : 03-05-2026
 */

#ifndef MENU_C 
#define MENU_C

#include <stdio.h>

#include "defs.h"

/**
 * Displays the Main Menu and controls Mantis' game navigation
 * @param m A pointer to the game structure containing the game data
 */
void mainMenu(Game *m)
{
    int option;

    printf("Main Menu\n");
    printf("  [1] New Game\n");
    printf("  [2] Top Players\n");
    printf("  [3] Settings\n");
    printf("  [0] Exit\n");

    askOption(&option, 0, 3);

    switch(option)
    {
        case 1: newGame(m); break;
        case 2: leaderBoard(m); break;
        case 3: gameSettings(m); break;
        case 0: printf("Exiting the game...\n"); break;
    }
}

/**
 * Asks the user for input with input validation
 * @param option A pointer to the user's chosen option
 * @param min The minimum number that can be inputted
 * @param max The maximum number that can be inputted
 */
void askOption(int *option, int min, int max)
{
    do
    {
        printf("\n>> ");
        scanf("%d", option);

        // Input Validation
        if (*option < min || max < *option)
            printf("Please select a valid option.");
    } while (*option < min || max < *option);
}

#endif // MENU_C;