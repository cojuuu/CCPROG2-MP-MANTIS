/**
 * Description : Contains the functions that handles the leaderboard of Mantis
 * Author/s : De Dios, Justin Marco C.
 *            Ocampo, Kysha Denise D.
 *  Section : S12A & S22A
 *  Last Modified : 03-05-2026
 */

#ifndef LEADERBOARD_C 
#define LEADERBOARD_C 

#include <stdio.h>
#include <string.h>
#include <conio.h>

#include "defs.h"

/**
 * Displays the Main Menu and controls Mantis' game navigation
 * @param m A pointer to the game structure containing the game data
 */
void leaderBoard(Game *m)
{
    char *lbOptions[] = {"T O P  P L A Y E R S (\033[3mWINS\033[0m)\n", "T O P  P L A Y E R S (\033[3mSCORE\033[0m)\n"};
    int selectedOption = 0;
    int input;
    bool optionSelected = false;

    do
    {
        printLogo();
        printf("\nLEADERBOARD\n\n");

        for (int i = 0; i < 2; i++)
        {
            if (i == selectedOption)
            {
                iSetColor(6);
                printf("\n\t%s\n", lbOptions[i]);
                iSetColor(0);
            }
            else
            {
                printf("%s\n", lbOptions[i]);
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
        case 1: sortPlayers(m, BY_WINS); displayLeaderboard(m, BY_WINS); break;
        case 2: sortPlayers(m, BY_SCORE); displayLeaderboard(m, BY_SCORE); break;
    }
}



// /**
//  * Displays the leaderboard menu and handles navigation in the different leaderboard views
//  * @param m A pointer to the game structure containing the game data
//  */
// void leaderBoard(Game *m)
// {
//     int option;

//     printf("Leaderboard\n");
//     printf("  [1] Top Players (Wins)\n");
//     printf("  [2] Top Players (Score)\n");

//     askOption(&option, 1, 2);

//     loadPlayerData(m);
    
//     switch(option)
//     {
//         case 1: sortPlayers(m, BY_WINS); displayLeaderboard(m, BY_WINS); break;
//         case 2: sortPlayers(m, BY_SCORE); displayLeaderboard(m, BY_SCORE); break;
//     }
// }



/**
 * Sorts an array of players from highest to lowest depending on the sort type
 * @param m A pointer to the game structure containing the game data
 * @param sortType Sorting method for arranging the players either by wins or scores
 * @return The function doesn't return anything
 */
void sortPlayers(Game *m, int sortType)
{
    Player temp;
    int i, j;
    bool shouldSwap;

    for (i = 0; i < m->totalPlayers; i++)
    {
        for (j = 0; j < m->totalPlayers - 1; j++)
        {
            if (sortType == BY_WINS)
                shouldSwap = m->playerData[j].wins < m->playerData[j + 1].wins;
            else if (sortType == BY_SCORE)
                shouldSwap = m->playerData[j].totalScore < m->playerData[j + 1].totalScore;

            if (shouldSwap)
            {
                temp = m->playerData[j];
                m->playerData[j] = m->playerData[j + 1];
                m->playerData[j + 1] = temp;
            } 
        }
    }
}

/**
 * Displays the Top 10 players depending on the display type
 * @param m A pointer to the game structure containing the game data
 * @param displayType Determines the display criteria of the leaderboard (wins or scores)
 * @return The function doesn't return anything
 */
void displayLeaderboard(Game *m, int displayType)
{
    bool emptyPlayerFound = false;
    int i = 0;

    if (displayType == BY_WINS)
    {
        do
        {
            if (strcmp(m->playerData[i].username, "") != 0)
                printf("%d: %s %d wins\n", i + 1, m->playerData[i].username, m->playerData[i].wins);
            else if (strcmp(m->playerData[i].username, "") == 0)
                emptyPlayerFound = true;

            i++;
        } while (i < TOP_10 && emptyPlayerFound == false);
    }
    else if (displayType == BY_SCORE)
    {
        do
        {
            if (strcmp(m->playerData[i].username, "") != 0)
                printf("%d: %s %d score\n", i + 1, m->playerData[i].username, m->playerData[i].totalScore);
            else if (strcmp(m->playerData[i].username, "") == 0)
                emptyPlayerFound = true;

            i++;
        } while (i < TOP_10 && emptyPlayerFound == false);
    }
}

#endif // LEADERBOARD_C; 