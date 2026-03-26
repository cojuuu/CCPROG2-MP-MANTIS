/**
 * Description : Contains the functions that handles the navigation of Mantis
 * Author/s : De Dios, Justin Marco C.
 *            Ocampo, Kysha Denise D.
 *  Section : S12A & S22A
 *  Last Modified : 03-27-2026
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
    String36 menuOptions[] = {"N E W  G A M E", "T O P  P L A Y E R S", "S E T T I N G S", "E X I T"};
    
    iClear(0, 0, 50, 50);
    printLogo();
    printf("\nMAIN MENU\n");
    interactiveMenu(&m->nav, menuOptions, 4);
    iClear(0, 0, CONSOLE_WIDTH, 20);
    switch(m->nav.selectedOption)
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
    setColor(MAGENTA);
    printf(" /$$      /$$  /$$$$$$  /$$   /$$ /$$$$$$$$ /$$$$$$  /$$$$$$ \n");
    printf("| $$$    /$$$ /$$__  $$| $$$ | $$|__  $$__/|_  $$_/ /$$__  $$\n");
    printf("| $$$$  /$$$$| $$  \\ $$| $$$$| $$   | $$     | $$  | $$  \\__/\n");
    printf("| $$ $$/$$ $$| $$$$$$$$| $$ $$ $$   | $$     | $$  |  $$$$$$ \n");
    printf("| $$  $$$| $$| $$__  $$| $$  $$$$   | $$     | $$   \\____  $$\n");
    printf("| $$\\  $ | $$| $$  | $$| $$\\  $$$   | $$     | $$   /$$  \\ $$\n");
    printf("| $$ \\/  | $$| $$  | $$| $$ \\  $$   | $$    /$$$$$$|  $$$$$$/\n");
    printf("|__/     |__/|__/  |__/|__/  \\__/   |__/   |______/ \\______/ \n");
    setColor(WHITE);
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
                printf("\n  >> %s\n", navOptions[i]);
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

        iClear(nav->x, nav->y, 50, optionCount * 2);
    } while (!nav->optionSelected);
}

#endif // MENU_C;