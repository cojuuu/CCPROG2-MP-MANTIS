/**
 * Description : Contains the functions that handles the navigation of Mantis
 * Author/s : De Dios, Justin Marco C.
 *            Ocampo, Kysha Denise D.
 *  Section : S12A & S22A
 *  Last Modified : 03-28-2026
 */

#ifndef MENU_C 
#define MENU_C

#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <conio.h>
#else
#include <conio_alt.h>
#endif

#include "defs.h"

/**
 * Displays the Main Menu and controls Mantis' game navigation
 * @param m A pointer to the game structure containing the game data
 * @return void
 */
void mainMenu(Game *m)
{
    String36 menuOptions[] = {"N E W  G A M E", "T O P  P L A Y E R S", "S E T T I N G S", "E X I T"};
    
    printLogo();
    printf("\nMAIN MENU\n");
    interactiveMenu1D(&m->nav, menuOptions, 4);
    iClear(0, 0, MANTIS_LOGO_WIDTH, 20);
    switch(m->nav.selectedOption)
    {
        case 0: selectPlayers(m); break;
        case 1: leaderBoard(m); break;
        case 2: gameSettings(m); break;
    }
}

/**
 * Prints the logo of Mantis
 * @return void
*/
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

/**
 * WS interactive menu
 * @param nav A pointer to the navigator variable (kbInput, selectedOption, cursorPos, selected, optionSelected)
 * @param navOptions Navigation options
 * @param optionCount Amount of navigation options
 * @return void
*/
void interactiveMenu1D(Navigator *nav, String36 navOptions[], int optionCount)
{
    int i;
    nav->selectedOption = 0;
    nav->optionSelected = false;

    getCursorPosition(&nav->cursorPos.x, &nav->cursorPos.y);
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

        iClear(nav->cursorPos.x, nav->cursorPos.y, CONSOLE_WIDTH, optionCount * 2);
    } while (!nav->optionSelected);
}

/**
 * WASD interactive menu
 * @param nav A pointer to the navigator variable (kbInput, selectedOption, cursorPos, selected, optionSelected)
 * @param navOptions Navigation options
 * @param rowOptCount Amount of rows in the navigation options
 * @param colOptCount Amount of columns in the navigation options
 * @return void
*/
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
            case 'W': nav->selected.y--; break;
            case 's':
            case 'S': 
                nav->selected.y++; 
                if (strcmp(navOptions[nav->selected.y][nav->selected.x], "") == 0)
                    nav->selected.y--;
                break;
            case 'a':
            case 'A': nav->selected.x--; break;
            case 'd':
            case 'D': 
                nav->selected.x++;
                if (strcmp(navOptions[nav->selected.y][nav->selected.x], "") == 0)
                    nav->selected.x--;  
                break;
            case ENTER_KEY: nav->optionSelected = true; break;
        }

        if (nav->selected.y > rowOptCount - 1)
            nav->selected.y = 0;
        else if (nav->selected.y < 0)
        {
            nav->selected.y = rowOptCount - 1;
            if (strcmp(navOptions[nav->selected.y][nav->selected.x], "") == 0)
                nav->selected.y = 0;   
        }
        else if (nav->selected.x > colOptCount - 1)
            nav->selected.x = 0;
        else if (nav->selected.x < 0)
        {
            nav->selected.x = colOptCount - 1;
            if (strcmp(navOptions[nav->selected.y][nav->selected.x], "") == 0)
                nav->selected.x = 0;   
        }
        
        iClear(nav->cursorPos.x, nav->cursorPos.y, CONSOLE_WIDTH, rowOptCount * 2);
    } while (!nav->optionSelected);
}

#endif // MENU_C;