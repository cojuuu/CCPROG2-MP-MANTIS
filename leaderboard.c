#ifndef LEADERBOARD_C 
#define LEADERBOARD_C 

#include <stdio.h>
#include <string.h>

#include "defs.h"

/**
 * Leaderboard menu of Mantis and handles user input based on what leaderboard they want to view
 * @param m A pointer to the game structure containing the game data
 * @return The function doesn't return anything
 */
void leaderBoard(Game *m)
{
    int option;

    printf("Leaderboard\n");
    printf("  [1] Top Players (Wins)\n");
    printf("  [2] Top Players (Score)\n");

    askOption(&option, 1, 2);

    loadPlayerData(m);
    
    switch(option)
    {
        case 1: sortPlayers(m, BY_WINS); displayLeaderboard(m, BY_WINS); break;
        case 2: sortPlayers(m, BY_SCORE); displayLeaderboard(m, BY_SCORE); break;
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
 * Displays the Top 10 players with either the highest wins or scores
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
