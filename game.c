#include <stdio.h>
#include <string.h>

#include "defs.h"

/**
 * Starts a new game of mantis from player selection to the actual game flow
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
 * Asks the user for input with input validation
 * @param selectedPlayers Selected players who will play the game
 * @param availPlayers Players extracted from the player file
 * @param playerCount Amount of players who will play the game
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
                    addPlayer(availPlayers, &totalPlayers); 
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
 * @param playerCount Amount of players who will play the game
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
 * Adjusts the player array by removing the chosen player and adjusts the position of the suceeding players
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
void addPlayer(Player availPlayers[], int *totalPlayers)
{
    FILE *playerFile;
    String36 newPlayer;
    bool foundEmptyPlayer = false;
    int i = 0;

    printf("New player username: ");
    scanf("%s", newPlayer);

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
 * Initializes a Player struct with empty values
 * @return The function returns the Player struct with empty values
 */
Player emptyPlayer()
{
    Player p = {"", 0, 0};

    return p;
}