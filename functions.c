/**
* Description : <short description of the file>
* Author/s : De Dios, Justin Marco C.
*            Ocampo, Kysha Denise D.
* Section : S12A & S22A
* Last Modified : 02-01-2026
*/

#ifndef FUNCTIONS_C
#define FUNCTIONS_C

#include <stdio.h>

#include "defs.h"

/**
 * Displays the Main Menu (New Game, Top Players, Settings, Exit) of Mantis
 */
void displayMainMenu()
{
    printf("Main Menu\n");
    printf("  [1] New Game\n");
    printf("  [2] Top Players\n");
    printf("  [3] Settings\n");
    printf("  [0] Exit\n");
}

/**
 * Asks the user for input with ">>"
 * @param input The user input based on a list of options
 */
void askInput(int *input)
{
    printf("\n>> ");
    scanf("%d", input);
}

#endif // FUNCTIONS_C;