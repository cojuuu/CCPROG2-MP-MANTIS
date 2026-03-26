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
#include <conio.h>

#include "defs.h"

/**
 * Displays the Main Menu and controls Mantis' game navigation
 * @param m A pointer to the game structure containing the game data
 */
void mainMenu(Game *m)
{
    char *menuOptions[] = {"N E W  G A M E\n", "T O P  P L A Y E R S\n", "S E T T I N G S\n", "E X I T\n"};
    int selectedOption = 0;
    int input;
    bool optionSelected = false;

    do
    {
        printLogo();
        printf("\nMAIN MENU\n\n");

        for (int i = 0; i < 4; i++)
        {
            if (i == selectedOption)
            {
                iSetColor(6);
                printf("\n\t%s\n", menuOptions[i]);
                iSetColor(0);
            }
            else
            {
                printf("%s\n", menuOptions[i]);
            }
        }

        input = getch();

        switch(input)
        {
            case 'w': 
            case 'W': selectedOption-= 1; break;
            case 's': 
            case 'S': selectedOption+= 1; break;
            case 13: optionSelected = true; break; // enter key
        }

        if (selectedOption > 3)
            selectedOption = 0;
        else if (selectedOption < 0)
            selectedOption = 3;

        iClear(0, 0, CONSOLE_WIDTH, CONSOLE_HEIGHT);
    } while (!optionSelected);

    switch(selectedOption)
    {
        case 0: newGame(m); break;
        case 1: leaderBoard(m); break;
        case 2: gameSettings(m); break;
        case 3: printf("Exiting game...\n"); break;
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

void printLogo()
{
    iSetColor(6);
    printf(" /$$      /$$  /$$$$$$  /$$   /$$ /$$$$$$$$ /$$$$$$  /$$$$$$ \n");
    printf("| $$$    /$$$ /$$__  $$| $$$ | $$|__  $$__/|_  $$_/ /$$__  $$\n");
    printf("| $$$$  /$$$$| $$  \\ $$| $$$$| $$   | $$     | $$  | $$  \\__/\n");
    printf("| $$ $$/$$ $$| $$$$$$$$| $$ $$ $$   | $$     | $$  |  $$$$$$ \n");
    printf("| $$  $$$| $$| $$__  $$| $$  $$$$   | $$     | $$   \\____  $$\n");
    printf("| $$\\  $ | $$| $$  | $$| $$\\  $$$   | $$     | $$   /$$  \\ $$\n");
    printf("| $$ \\/  | $$| $$  | $$| $$ \\  $$   | $$    /$$$$$$|  $$$$$$/\n");
    printf("|__/     |__/|__/  |__/|__/  \\__/   |__/   |______/ \\______/ \n");
    iSetColor(0);
}

void interactiveMenu(Navigator *nav, String36 navOptions[], int optionCount)
{
    int i;
    nav->selectedOption = 0;
    nav->optionSelected = false;

    getCursorPosition(&nav->x, &nav->y);
    do
    {
        for (i = 0; i < optionCount; i++)
        {
            if (i == nav->selectedOption)
            {
                iSetColor(7);
                printf("\n  %s <<\n", navOptions[i]);
                iSetColor(0);
            }
            else
            {
                printf("\n%s\n", navOptions[i]);
            }
        }

        nav->kbInput = getch();

        switch (nav->kbInput)
        {
            case w_KEY:
            case W_KEY: nav->selectedOption--; break;
            case s_KEY:
            case S_KEY: nav->selectedOption++; break;
            case ENTER_KEY: nav->optionSelected = true; break;
        }

        if (nav->selectedOption > optionCount - 1)
            nav->selectedOption = 0;
        else if (nav->selectedOption < 0)
            nav->selectedOption = optionCount - 1;

        if (!nav->optionSelected)
            iClear(nav->x, nav->y, 50, optionCount * 2);
    } while (!nav->optionSelected);
}

#endif // MENU_C;