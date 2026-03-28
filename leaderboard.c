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
    String36 lbOptions[] = {"T O P  P L A Y E R S (WIN)", "T O P  P L A Y E R S (SCORE)", "B A C K"};

    printLogo();
    printf("\nLEADERBOARD\n");
    interactiveMenu(&m->nav, lbOptions, 3);

    loadPlayerData(m);
    switch(m->nav.selectedOption)
    {
        case 0: sortPlayers(m, BY_WINS); displayLeaderboard(m, BY_WINS); break;
        case 1: sortPlayers(m, BY_SCORE); displayLeaderboard(m, BY_SCORE); break;
        case 2: iClear(0, 0, CONSOLE_WIDTH, CONSOLE_HEIGHT); mainMenu(m); break;
    }
}



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

    iClear(0, 0, MANTIS_LOGO_WIDTH, MANTIS_LOGO_HEIGHT);
    printLogo();
    printf("\nTOP PLAYERS\n");
    printf("\n              P L A Y E R  R A N K I N G\n");   

    if (displayType == BY_WINS)
    {
        for(i = 0; i < TOP_10 && emptyPlayerFound == false; i++)
        {
             if(strcmp(m->playerData[i].username, "") == 0)
            {
                emptyPlayerFound = true;
            }else
            {
            if(i < 3)
            {
                if(i == 0)
                {
                    displayPodium(m, displayType);
                }
            }else
            {
                if(i == 3)
                {
                printf("     +------+----------------------+------------+\n");
                printf("     | RANK | USERNAME             | WINS       |\n");
                printf("     +------+----------------------+------------+\n");
                }
            printf("     | %-4d | %-20s | %-10d |\n", i + 1, m->playerData[i].username, m->playerData[i].wins);
            }
            }
        }
        printf("     +------+----------------------+------------+\n");
    }
    else if (displayType == BY_SCORE)
    {
        for(i = 0; i < TOP_10 && emptyPlayerFound == false; i++)
        {
             if(strcmp(m->playerData[i].username, "") == 0)
            {
                emptyPlayerFound = true;
            }else
            
            if(i < 3)
            {
                if(i == 0)
                {
                    displayPodium(m, displayType);
                }
            }else
            {
                if(i == 3)
                {
                printf("      +------+----------------------+------------+\n");
                printf("      | RANK | USERNAME             | SCORE      |\n");
                printf("      +------+----------------------+------------+\n");
                }
            printf("      | %-4d | %-20s | %-10d |\n", i + 1, m->playerData[i].username, m->playerData[i].totalScore);
            }
        }
        printf("      +------+----------------------+------------+\n");
    }

    setColor(MAGENTA);
    waitEnter("\t    Press enter to go back...");
    setColor(WHITE);

    iClear(0, 0, CONSOLE_WIDTH, CONSOLE_HEIGHT);
    leaderBoard(m);
}

/**
 * Displays the podium for the top 3 players depending on the display type
 * @param m A pointer to the game structure containing the game data
 * @param displayType Determines the display criteria of the leaderboard (wins or scores)
 * @return The function doesn't return anything
 */
void displayPodium(Game *m, int displayType)
{
    int boxWidth = 16;
    int nameLen, totalSpace, leftSpace, rightSpace;

    if (displayType == BY_WINS)
    {
        iSetColor(4);
        nameLen = strlen(m->playerData[0].username);
        totalSpace = boxWidth - nameLen;
        leftSpace = totalSpace / 2;
        rightSpace = totalSpace - leftSpace;

        printf("                        1 s t\n");
        printf("                   ________________\n");
        printf("                  |                |\n");
        printf("      2 n d       |%*s%.12s%*s|\n", leftSpace, "", m->playerData[0].username, rightSpace, "");
        printf(" ________________ |   WINS: %-4d   |\n", m->playerData[0].wins);
        printf("|                ||                |     3 r d\n");
        nameLen = strlen(m->playerData[1].username);
        totalSpace = boxWidth - nameLen;
        leftSpace = totalSpace / 2;
        rightSpace = totalSpace - leftSpace;

        printf("|%*s%.12s%*s||                | ________________\n", leftSpace, "", m->playerData[1].username, rightSpace, "");
        printf("|   WINS: %-4d   ||                ||                |\n", m->playerData[1].wins);
        nameLen = strlen(m->playerData[2].username);
        totalSpace = boxWidth - nameLen;
        leftSpace = totalSpace / 2;
        rightSpace = totalSpace - leftSpace;

        printf("|                ||                ||%*s%.12s%*s|\n", leftSpace, "", m->playerData[2].username, rightSpace, "");
        printf("|                ||                ||   WINS: %-4d   |\n", m->playerData[2].wins);
        printf("|________________||________________||________________|\n\n\n");           

         iSetColor(0);
    }
    else if(displayType == BY_SCORE)
    {
        iSetColor(4);
        nameLen = strlen(m->playerData[0].username);
        totalSpace = boxWidth - nameLen;
        leftSpace = totalSpace / 2;
        rightSpace = totalSpace - leftSpace;

          printf("                        1 s t\n");
        printf("                   ________________\n");
        printf("                  |                |\n");
        printf("      2 n d       |%*s%.12s%*s|\n", leftSpace, "", m->playerData[0].username, rightSpace, "");
        printf(" ________________ |   SCORE: %-4d  |\n", m->playerData[0].totalScore);
        printf("|                ||                |     3 r d\n");
        nameLen = strlen(m->playerData[1].username);
        totalSpace = boxWidth - nameLen;
        leftSpace = totalSpace / 2;
        rightSpace = totalSpace - leftSpace;

        printf("|%*s%.12s%*s||                | ________________\n", leftSpace, "", m->playerData[1].username, rightSpace, "");
        printf("|   SCORE: %-4d  ||                ||                |\n", m->playerData[1].totalScore);
        nameLen = strlen(m->playerData[2].username);
        totalSpace = boxWidth - nameLen;
        leftSpace = totalSpace / 2;
        rightSpace = totalSpace - leftSpace;
        
        printf("|                ||                ||%*s%.12s%*s|\n", leftSpace, "", m->playerData[2].username, rightSpace, "");
        printf("|                ||                ||   SCORE: %-4d  |\n", m->playerData[2].totalScore);
        printf("|________________||________________||________________|\n\n\n");           

         iSetColor(0);
    }
}

#endif // LEADERBOARD_C; 