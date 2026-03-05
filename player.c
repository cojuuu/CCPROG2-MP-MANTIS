/**
 * Description : Contains the functions that handles the navigation of Mantis
 * Author/s : De Dios, Justin Marco C.
 *            Ocampo, Kysha Denise D.
 *  Section : S12A & S22A
 *  Last Modified : 03-05-2026
 */

#ifndef PLAYER_C 
#define PLAYER_C 

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "defs.h"

/**
 * Selects from a list of available players with the option to add a new player
 * @param m A pointer to the game structure containing the game data
 */
void selectPlayers(Game *m)
{
    int i, option;
    bool playerDataLoaded, playerAdded;

    printf("How many players?\n");
    askOption(&m->playerCount, MIN_PLAYERS, MAX_PLAYERS);

    for (i = 0; i < m->playerCount; i++)
    {
        m->activePlayers[i] = emptyPlayer();
    }
    
    // Load player file
    playerDataLoaded = loadPlayerData(m);
    
    if (playerDataLoaded)
    {
        for (i = 0; i < m->playerCount; i++)
        {
            displayChosenPlayers(m);

            printf("\nSelect Player %d\n", i + 1);
            printf("  [0] <Add new player>\n");

            displayAvailPlayers(m, i);

            do
            {
                askOption(&option, 0, m->totalPlayers - i);

                if (m->totalPlayers >= 50 && option == 0)
                    printf("Maximum player reached! Please select another option.");
            } while (m->totalPlayers >= 50 && option == 0);

            playerAdded = false;
            switch(option)
            {
                case 0: 
                    addNewPlayer(m); 
                    playerAdded = true; 
                    i--;
                    break;
                default: 
                    m->activePlayers[i] = m->playerData[option - 1]; 
                    break;
            }

            if (!playerAdded)
                adjustPlayerArr(m, option - 1);
        }

        displayChosenPlayers(m);
    }
}

/**
 * Displays the chosen players for the game
 * @param m A pointer to the game structure containing the game data
 */
void displayChosenPlayers(Game *m)
{
    int i;

    for (i = 0; i < m->playerCount; i++)
    {
        if (strcmp(m->activePlayers[i].username, "") == 0)
            printf("  P%d: ?\n", i + 1);
        else
            printf("  P%d: %s\n", i + 1, m->activePlayers[i].username);
    }
}

/**
 * Displays the players who have not yet been chosen
 * @param m A pointer to the game structure containing the game data
 * @param playersChosen Amount of players already chosen
 */
void displayAvailPlayers(Game *m, int playersChosen)
{
    int i;

    for (i = 0; i < m->totalPlayers - playersChosen; i++)
    {
        printf("  [%d] %s\n", i + 1, m->playerData[i].username);
    }
}

/**
 * Adjusts the player array by removing the chosen player and adjusting the position of the succeeding players
 * @param m A pointer to the game structure containing the game data
 * @param selectedPlayers Index of the selected player who will play the game
 */
void adjustPlayerArr(Game *m, int selectedPlayer)
{
    int i;

    for (i = selectedPlayer; i < m->totalPlayers - 1; i++)
    {
        m->playerData[i] = m->playerData[i + 1];
    }

    m->playerData[i] = emptyPlayer();
}

/**
 * Adds a player to the array of available players
 * @param m A pointer to the game structure containing the game data
 */
void addNewPlayer(Game *m)
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
            duplicateExist = playerFound(m, temp);

            if (duplicateExist)
                printf("Username already exists!\n");
        }

    } while (strlen(temp) > 36 || duplicateExist);

    strcpy(newPlayer, temp);

    // Increment total players
    m->totalPlayers++;

    // Find empty player in availPlayer arr
    do
    {
        // Update player data in game
        if (strcmp(m->playerData[i].username, "") == 0)
        {
            strcpy(m->playerData[i].username, newPlayer);
            foundEmptyPlayer = true;
        }

        i++;
    } while (i < m->totalPlayers && !foundEmptyPlayer);

    // Open player file
    playerFile = fopen("players.txt", "a");

    // Append new player into file
    fprintf(playerFile, "\n%s,0,0", newPlayer);

    fclose(playerFile);
}

/**
 * Checks if the new player's username already exist
 * @param m A pointer to the game structure containing the game data
 * @param newPlayer Username of the new player
 * @return True If the username already exist
 * @return False Otherwise
 */
bool playerFound(Game *m, String36 newPlayer)
{
    int i = 0;
    bool foundPlayer = false;

    do
    {
        if (strcmp(newPlayer, m->playerData[i].username) == 0)
            foundPlayer = true;
        
        i++;
    } while (foundPlayer == false && i < m->totalPlayers);

    return foundPlayer;
}

/**
 * Initializes a Player with empty values
 * @return Player with empty values
 */
Player emptyPlayer()
{
    Player p = {"", 0, 0};

    return p;
}

#endif // PLAYER_C;