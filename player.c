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
    char *playerCountOption[] = {"3 Players   ", "4 Players\n",
         "5 Players   ", "6 Players\n"};
    int selectedPlayerCount = 0;
    int input;
    bool playerCountSelected = false;
    int i, Option;
    bool playerDataLoaded, playerAdded;
   
    do
    {        
         printf("-----------------------------------------\n\n");
         printf("        [ PLAYER CONFIGURATION ]              \n\n");
         printf("-----------------------------------------\n\n");
         printf("    Please define player count (%d-%d):        \n\n\n", MIN_PLAYERS, MAX_PLAYERS);

        for (int i = 0; i < 4; i++)
        {
            if (i == selectedPlayerCount)
            {
                iSetColor(6);
                printf("\t%s", playerCountOption[i]);
                iSetColor(0);
            }
            else
            {
                printf("\t%s", playerCountOption[i]);
            }
        }

        printf("\n-----------------------------------------\n");

        input = getch();

        switch(input)
        {
            case 'w': 
            case 'W': selectedPlayerCount-= 1; break;
            case 's': 
            case 'S': selectedPlayerCount+= 1; break;
            case 13: playerCountSelected = true; break; // enter key
        }

        if (selectedPlayerCount > 3)
        {
            selectedPlayerCount = 0;
        }
        else if (selectedPlayerCount < 0)
        {
            selectedPlayerCount = 3;
        }

            iClear(0, 0, CONSOLE_WIDTH, CONSOLE_HEIGHT);
    } while (!playerCountSelected);

    switch(selectedPlayerCount)
    {
        case 0: m->playerCount = 3; break;
        case 1: m->playerCount = 4; break;
        case 2: m->playerCount = 5; break;
        case 3: m->playerCount = 6; break;
    }

    printf("\n--------------------------------------------------------\n\n");

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
                askOption(&Option, 0, m->totalPlayers - i);

                if (m->totalPlayers >= 50 && Option == 0)
                    printf("Maximum player reached! Please select another option.");
            } while (m->totalPlayers >= 50 && Option == 0);

            playerAdded = false;
            switch(Option)
            {
                case 0: 
                    addNewPlayer(m); 
                    playerAdded = true; 
                    i--;
                    break;
                default: 
                    m->activePlayers[i] = m->playerData[Option - 1]; 
                    break;
            }

            if (!playerAdded)
                adjustPlayerArr(m, Option - 1);
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
    printf("INITIALIZING PLAYERS...\n\n\n");

    int playerRow;
    int playersPerRow = 3;
    int i;

    for (playerRow = 0; playerRow < m->playerCount; playerRow += playersPerRow)
    {
        for (i = playerRow; i < playerRow + playersPerRow && i < m->playerCount; i++)
        {
            if (strcmp(m->activePlayers[i].username, "") == 0)
                printf("  [ PLAYER %d: ? ]  ", i + 1);
            else{
                iSetColor(6);
                printf("  [ PLAYER %d: %s ]  ", i + 1, m->activePlayers[i].username);
                iSetColor(0); // Reset color
            }
        }
        printf("\n");
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