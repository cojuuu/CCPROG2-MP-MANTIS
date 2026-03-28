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
#include <string.h>

#ifdef _WIN32
#include <conio.h>
#else
#include "conhelper.h"
#endif

#include "defs.h"

/**
 * Displays the Main Menu and controls Mantis' game navigation
 * @param m A pointer to the game structure containing the game data
 */
void mainMenu(Game *m)
{
    String36 menuOptions[] = {"N E W  G A M E", "T O P  P L A Y E R S", "S E T T I N G S", "E X I T"};
    
    printLogo();
    printf("\nMAIN MENU\n");
    interactiveMenu(&m->nav, menuOptions, 4);
    iClear(0, 0, MANTIS_LOGO_WIDTH, 20);
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
                setColor(MAGENTA);
                printf("\n  >> %s\n", navOptions[i]);
                setColor(WHITE);
            }
            else
            {
                printf("\n%s\n", navOptions[i]);
            }
        }

        nav->kbInput = getch();

        switch (nav->kbInput)
        {
            case 'w':
            case 'W': nav->selectedOption--; break;
            case 's':
            case 'S': nav->selectedOption++; break;
            case ENTER_KEY: nav->optionSelected = true; break;
        }

        if (nav->selectedOption > optionCount - 1)
            nav->selectedOption = 0;
        else if (nav->selectedOption < 0)
            nav->selectedOption = optionCount - 1;

        iClear(nav->x, nav->y, CONSOLE_WIDTH, optionCount * 2);
    } while (!nav->optionSelected);
}

void interactiveMenu2D(Navigator *nav, String36 navOptions[][MAX_OPT_COL], int rowOptCount, int colOptCount)
{
    int x, y;
    nav->selected.x = 0;
    nav->selected.y = 0;
    nav->optionSelected = false;

    getCursorPosition(&nav->cursorPos.x, &nav->cursorPos.y);
    do
    {
        for (y = 0; y < rowOptCount; y++)
        {
            for (x = 0; x < colOptCount; x++)
            {
                if ((x == nav->selected.x) && (y == nav->selected.y))
                {
                    setColor(MAGENTA);
                    printf(">> %-36s", navOptions[y][x]);
                    setColor(WHITE);
                }
                else
                {
                    printf("   %-36s", navOptions[y][x]);
                }
            }
            printf("\n\n");
        }

        nav->kbInput = getch();

        switch (nav->kbInput)
        {
            case 'w':
            case 'W': 
                nav->selected.y--; 
                break;
            case 's':
            case 'S': 
                nav->selected.y++; 
                break;
            case 'a':
            case 'A': 
                nav->selected.x--; 
                break;
            case 'd':
            case 'D': 
                nav->selected.x++;  
                break;
            case ENTER_KEY: nav->optionSelected = true; break;
        }

        if (nav->selected.y > rowOptCount - 1)
            nav->selected.y = 0;
        else if (nav->selected.y < 0)
            nav->selected.y = rowOptCount - 1;
        else if (nav->selected.x > colOptCount - 1)
            nav->selected.x = 0;
        else if (nav->selected.x < 0)
            nav->selected.x = colOptCount - 1;

        iClear(nav->cursorPos.x, nav->cursorPos.y, CONSOLE_WIDTH, rowOptCount * 2);
    } while (!nav->optionSelected);
}

void printGameOver()
{
    setColor(MAGENTA);
    printf("  /$$$$$$   /$$$$$$  /$$      /$$ /$$$$$$$$        /$$$$$$  /$$    /$$ /$$$$$$$$ /$$$$$$$ \n");
    printf(" /$$__  $$ /$$__  $$| $$$    /$$$| $$_____/       /$$__  $$| $$   | $$| $$_____/| $$__  $$\n");
    printf("| $$  \\__/| $$  \\ $$| $$$$  /$$$$| $$            | $$  \\ $$| $$   | $$| $$      | $$  \\ $$\n");
    printf("| $$ /$$$$| $$$$$$$$| $$ $$ /$$$$| $$$$$         | $$  | $$|  $$ / $$/| $$$$$   | $$$$$$$/\n");
    printf("| $$|_  $$| $$__  $$| $$  $$$| $$| $$__/         | $$  | $$ \\  $$ $$/ | $$__/   | $$__  $$\n");
    printf("| $$  \\ $$| $$  | $$| $$\\  $ | $$| $$            | $$  | $$  \\  $$$/  | $$      | $$  \\ $$\n");
    printf("|  $$$$$$/| $$  | $$| $$ \\/  | $$| $$$$$$$$      |  $$$$$$/   \\  $/   | $$$$$$$$| $$  | $$\n");
    printf(" \\______/ |__/  |__/|__/     |__/|________/       \\______/     \\_/    |________/|__/  |__/\n");
    setColor(WHITE);
}

#endif // MENU_C;