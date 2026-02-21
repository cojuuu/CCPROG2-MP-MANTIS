#include <stdio.h>

#include "defs.h"

/**
 * Displays the Main Menu (New Game, Top Players, Settings, Exit) of Mantis
 * @return The function doesn't return anything
 */
void mainMenu(int *option)
{
    printf("Main Menu\n");
    printf("  [1] New Game\n");
    printf("  [2] Top Players\n");
    printf("  [3] Settings\n");
    printf("  [0] Exit\n");

    askOption(option, 0, 3);
}

/**
 * Asks the user for input with input validation
 * @param option The user input based on a list of options
 * @param min The minimum number
 * @param max The maximum number
 * @return The function updates the address of option with the player's chosen option
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