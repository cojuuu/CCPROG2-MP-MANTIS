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
    String36 playerCountOptions[][MAX_OPT_COL] = {{"3 Players", "4 Players"},
                                                  {"5 Players", "6 Players"}};
    bool playerDataLoaded;
    int i;

    printf("-----------------------------------------\n\n");
    printf("        [ PLAYER CONFIGURATION ]              \n\n");
    printf("-----------------------------------------\n\n");
    printf("    Please define player count (%d-%d):        \n\n\n", MIN_PLAYERS, MAX_PLAYERS);
    interactiveMenu2D(&m->nav, playerCountOptions, 2, 2);
    iClear(0, 0, CONSOLE_WIDTH, CONSOLE_HEIGHT);

    if (m->nav.selected.x == 0 && m->nav.selected.y == 0)
        m->playerCount = 3;
    else if (m->nav.selected.x == 1 && m->nav.selected.y == 0)
        m->playerCount = 4;
    else if (m->nav.selected.x == 0 && m->nav.selected.y == 1)
        m->playerCount = 5;
    else if (m->nav.selected.x == 1 && m->nav.selected.y == 1)
        m->playerCount = 6;

    playerDataLoaded = loadPlayerData(m);
    
    if (playerDataLoaded)
    {
        for (i = 0; i < m->playerCount; i++)
        {
            displayChosenPlayers(m);
            displayAvailPlayers(m, i);

            if (m->chosenPlayer == -1)
            {
                addNewPlayer(m);
                i--;
            }
            else
            { 
                m->activePlayers[i] = m->playerData[m->chosenPlayer];
                adjustPlayerArr(m, m->chosenPlayer);
            }

            iClear(0, 0, CONSOLE_WIDTH, CONSOLE_HEIGHT);
        }
            /*
        displayChosenPlayers(m);
        iClear(0, 0, CONSOLE_WIDTH, CONSOLE_HEIGHT);
         }
        }
        */
    }
}

/**
 * Displays the chosen players for the game
 * @param m A pointer to the game structure containing the game data
 */
void displayChosenPlayers(Game *m)
{
    int i;
    int nChosenPlayers = 0;

    for(i = 0; i < m->playerCount; i++)
    {
        if(strcmp(m->activePlayers[i].username, "") != 0)
            nChosenPlayers++;
    }

    printf("\n--------------------------------------------------------\n");
    printf("\nINITIALIZING PLAYERS...");
    setColor(MAGENTA);
    printf("                            %d / %d\n\n\n", nChosenPlayers, m->playerCount);
    setColor(WHITE);

    for (i = 0; i < m->playerCount; i++)
    {
        if (strcmp(m->activePlayers[i].username, "") == 0)
            printf("  [ PLAYER %d: ? ]  ", i + 1);
        else
        {
            setColor(MAGENTA);
            printf("  [ PLAYER %d: %s ]  ", i + 1, m->activePlayers[i].username);
            setColor(WHITE);
        }

        if (i % 3 == 2)
            printf("\n\n");
    }
}

/**
 * Displays the players who have not yet been chosen
 * @param m A pointer to the game structure containing the game data
 * @param playersChosen Amount of players already chosen
 * @param selectedPlayer Index of the currently selected player
 */
void displayAvailPlayers(Game *m, int playersChosen)
{
    String36 selectPlayerOptions[17][MAX_OPT_COL];
    int i;
    int col = 0, row = 0;

    memset(selectPlayerOptions, 0, sizeof(selectPlayerOptions));

    strcpy(selectPlayerOptions[0][0], "[Add new player]");
    col = 1;

    for (i = 0; i < m->totalPlayers; i++)
    {
        if (col == MAX_OPT_COL)
        {
            col = 0;
            row++;
        }

        strcpy(selectPlayerOptions[row][col], m->playerData[i].username);
        col++;
    }

    printf("\nSELECT PLAYER %d\n\n\n", playersChosen + 1);
    interactiveMenu2D(&m->nav, selectPlayerOptions, row + 1, MAX_OPT_COL);

    m->chosenPlayer = searchPlayer(selectPlayerOptions[m->nav.selected.y][m->nav.selected.x], m->playerData);
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
        iSetColor(6);
        scanf("%s", temp);
        iSetColor(0);

        if (strlen(temp) > 36)
         {   iSetColor(1);
            printf("!! Username can only be 36 characters !!\n\n");
            iSetColor(0);
        }
        else
        {
            duplicateExist = playerFound(m, temp);

            if (duplicateExist)
            {
                iSetColor(1);
                printf("!! Username already exists !!\n\n");
                iSetColor(0);
            }
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

int searchPlayer(String36 currentPlayer, Player playerList[])
{
    int i = 0;
    int playerIndex = -1;
    bool playerFound = false;

    do
    {
        if (strcmp(currentPlayer, playerList[i].username) == 0)
        {
            playerIndex = i;
            playerFound = true;
        }

        i++;
    } while (!playerFound);
    
    return playerIndex;
}

#endif // PLAYER_C;