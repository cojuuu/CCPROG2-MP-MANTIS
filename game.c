#ifndef GAME_C 
#define GAME_C 

#include <stdio.h>
#include <string.h>

#include "defs.h"

/**
 * Starts a new game of Mantis from player selection to the actual game flow
 * @return The function doesn't return anything
 */
void newGame()
{
    Player activePlayers[MAX_PLAYERS], availPlayers[MAX_PLAYER_DATA];
    int playerCount;

    // Ask how many players will play
    printf("How many players?\n");
    askOption(&playerCount, MIN_PLAYERS, MAX_PLAYERS);

    // Select Players
    selectPlayers(activePlayers, availPlayers, playerCount);

    // Game Loop
}

/**
 * Selects players from available players
 * @param selectedPlayers Selected players who will play the game
 * @param availPlayers Players extracted from the player file
 * @param playerCount Number of players who will play the game
 * @return The function doesn't return anything
 */
void selectPlayers(Player selectedPlayers[], Player availPlayers[], int playerCount)
{
    int i, option, totalPlayers = 0;
    bool playerDataLoaded, playerAdded;

    // Initialize usernames to an empty string
    for (i = 0; i < playerCount; i++)
    {
        selectedPlayers[i] = emptyPlayer();
    }
    
    // Load player file
    playerDataLoaded = loadPlayerData(availPlayers, &totalPlayers);
    printf("Total player: %d\n", totalPlayers);
    if (playerDataLoaded)
    {
        for (i = 0; i < playerCount; i++)
        {
            displayChosenPlayers(selectedPlayers, playerCount);

            printf("\nSelect Player %d\n", i + 1);
            printf("  [0] <Add new player>\n");

            displayAvailPlayers(availPlayers, totalPlayers - i);

            do
            {
                askOption(&option, 0, totalPlayers - i);

                if (totalPlayers >= 50 && option == 0)
                    printf("Maximum player reached! Please select another option.");
            } while (totalPlayers >= 50 && option == 0);

            playerAdded = false;
            switch(option)
            {
                case 0: 
                    addPlayer(availPlayers, selectedPlayers, &totalPlayers); 
                    playerAdded = true; 
                    i--;
                    break;
                default: 
                    selectedPlayers[i] = availPlayers[option - 1]; 
                    break;
            }

            if (!playerAdded)
                adjustPlayerArr(availPlayers, option - 1, totalPlayers - i);
        }

        displayChosenPlayers(selectedPlayers, playerCount);
    }
}

/**
 * Displays the chosen players for the game
 * @param selectedPlayers Selected players who will play the game
 * @param playerCount Number of players who will play the game
 * @return The function doesn't return anything
 */
void displayChosenPlayers(Player selectedPlayers[], int playerCount)
{
    int i;

    for (i = 0; i < playerCount; i++)
    {
        if (strcmp(selectedPlayers[i].username, "") == 0)
            printf("  P%d: ?\n", i + 1);
        else
            printf("  P%d: %s\n", i + 1, selectedPlayers[i].username);
    }
}

/**
 * Displays the available players of the game
 * @param availPlayers Players extracted from the player file
 * @param totalPlayers Total available players
 * @return The function doesn't return anything
 */
void displayAvailPlayers(Player availPlayers[], int totalPlayers)
{
    int i;

    for (i = 0; i < totalPlayers; i++)
    {
        printf("  [%d] %s\n", i + 1, availPlayers[i].username);
    }
}

/**
 * Adjusts the player array by removing the chosen player and adjusting the position of the succeeding players
 * @param availPlayers Players extracted from the player file
 * @param selectedPlayers Selected players who will play the game
 * @param totalPlayers Total available players
 * @return The function doesn't return anything
 */
void adjustPlayerArr(Player availPlayers[], int selectedPlayer, int totalPlayers)
{
    int i;

    for (i = selectedPlayer; i < totalPlayers - 1; i++)
    {
        availPlayers[i] = availPlayers[i + 1];
    }

    availPlayers[i] = emptyPlayer();
}

/**
 * Adds a player to the array of available players
 * @param availPlayers Players extracted from the player file
 * @param totalPlayers Total available players
 * @return The function doesn't return anything
 */
void addPlayer(Player availPlayers[], Player selectedPlayers[], int *totalPlayers)
{
    FILE *playerFile;
    String36 newPlayer;
    String100 temp;
    bool foundEmptyPlayer = false;
    bool duplicateExist;
    int i = 0;

    do
    {
        printf("New player username: ");
        scanf("%s", temp);

        if (strlen(temp) > 36)
            printf("Username can only be 36 characters!\n");
        else
        {
            duplicateExist = playerFound(availPlayers, temp, *totalPlayers);

            if (duplicateExist)
                printf("Username already exists!\n");
        }

    } while (strlen(temp) > 36 || duplicateExist);

    strcpy(newPlayer, temp);

    // Increment total players
    *totalPlayers += 1;

    // Find empty player in availPlayer arr
    do
    {
        // Update player data in game
        if (strcmp(availPlayers[i].username, "") == 0)
        {
            strcpy(availPlayers[i].username, newPlayer);
            foundEmptyPlayer = true;
        }

        i++;
    } while (i < *totalPlayers && !foundEmptyPlayer);

    // Open player file
    playerFile = fopen("players.txt", "a");

    // Append new player into file
    fprintf(playerFile, "\n%s,0,0", newPlayer);

    fclose(playerFile);
}

/**
 * Checks if the new player's username already exist
 * @param availPlayers Players extracted from the player file
 * @param newPlayer Username of the new player
 * @param totalPlayers Total available players
 * @return True If the username already exist
 * @return False Otherwise
 */
bool playerFound(Player availPlayers[], String36 newPlayer, int totalPlayers)
{
    int i = 0;
    bool foundPlayer = false;

    do
    {
        if (strcmp(newPlayer, availPlayers[i].username) == 0)
            foundPlayer = true;
        
        i++;
    } while (foundPlayer == false && i < totalPlayers);

    return foundPlayer;
}

/**
 * Initializes a Player struct with empty values
 * @return The function returns the Player struct with empty values
 */
Player emptyPlayer()
{
    Player p = {"", 0, 0};

    return p;
}

#endif // GAME_C;
