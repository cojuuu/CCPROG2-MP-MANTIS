#ifndef LEADERBOARD_C 
#define LEADERBOARD_C 

#include <stdio.h>

#include "defs.h"

/**
 * Leaderboard menu of Mantis
 * @return The function doesn't return anything
 */
void leaderBoard()
{
    Player playerData[MAX_PLAYER_DATA];
    int option;
    int totalPlayerData = 0;

    displayLeaderBoardMenu(&option);
    loadPlayerData(playerData, &totalPlayerData);

    switch(option)
    {
        case 1: leaderBoardWins(playerData, totalPlayerData); break;
        case 2: leaderBoardScore(playerData, totalPlayerData); break;
    }
}

/**
 * Displays the different options of the leaderboard menu
 * @return The function updates the option variable to the user's chosen leaderboard view
 */
void displayLeaderBoardMenu(int *option)
{
    printf("Leaderboard\n");
    printf("  [1] Top Players (Wins)\n");
    printf("  [2] Top Players (Score)\n");

    askOption(option, 1, 2);
}

/**
 * Leaderboard of the Top 10 players with the most wins
 * @return The function doesn't return anything
 */
void leaderBoardWins(Player playerData[], int totalPlayerData)
{
    Player temp;
    int i, j;

    // Sorts player data from highest to lowest (wins)
    for (i = 0; i < totalPlayerData; i++)
    {
        for (j = 0; j < totalPlayerData - 1; j++)
        {
            if (playerData[j].wins < playerData[j + 1].wins)
            {
                temp = playerData[j];
                playerData[j] = playerData[j + 1];
                playerData[j + 1] = temp;
            }
        }
    }

    // Display Leaderboard
    if (totalPlayerData < TOP_10)
    {
        for (i = 0; i < totalPlayerData; i++)
        {
            printf("%d: %s %d wins\n", i + 1, playerData[i].username, playerData[i].wins);
        }
    }
    else
    {
        for (i = 0; i < TOP_10; i++)
        {
            printf("%d: %s %d wins\n", i + 1, playerData[i].username, playerData[i].wins);
        }
    }
}

/**
 * Leaderboard of the Top 10 players with the highest scores
 * @return The function doesn't return anything
 */
void leaderBoardScore(Player playerData[], int totalPlayerData)
{
    Player temp;
    int i, j;

    // Sorts player data from highest to lowest (wins)
    for (i = 0; i < totalPlayerData; i++)
    {
        for (j = 0; j < totalPlayerData - 1; j++)
        {
            if (playerData[j].score < playerData[j + 1].score)
            {
                temp = playerData[j];
                playerData[j] = playerData[j + 1];
                playerData[j + 1] = temp;
            }
        }
    }

    // Display Leaderboard
    if (totalPlayerData < TOP_10)
    {
        for (i = 0; i < totalPlayerData; i++)
        {
            printf("%d: %s %d score\n", i + 1, playerData[i].username, playerData[i].score);
        }
    }
    else
    {
        for (i = 0; i < TOP_10; i++)
        {
            printf("%d: %s %d score\n", i + 1, playerData[i].username, playerData[i].score);
        }
    }
}

#endif // LEADERBOARD_C; 
