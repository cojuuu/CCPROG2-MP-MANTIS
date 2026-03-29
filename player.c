/**
 * Description : Contains the functions that handles the navigation of Mantis
 * Author/s : De Dios, Justin Marco C.
 *            Ocampo, Kysha Denise D.
 *  Section : S12A & S22A
 *  Last Modified : 03-29-2026
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
 * @return void
 */
void selectPlayers(Game *m)
{
    String36 playerCountOptions[][MAX_OPT_COL] = {{"3 Players", "4 Players"},
                                                  {"5 Players", "6 Players"}};
    bool playerDataLoaded;
    int i;

    printf("---------------------------------------------------\n\n");
    printf("             [ PLAYER CONFIGURATION ]              \n\n");
    printf("---------------------------------------------------\n\n");
    printf("        Please define player count (%d-%d):        \n\n\n", MIN_PLAYERS, MAX_PLAYERS);
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

            if (m->chosenPlayer == -1 && m->totalPlayers < MAX_PLAYER_DATA)
            {
                addNewPlayer(m);
                i--;
            }
            else if (m->chosenPlayer == -1 && m->totalPlayers == MAX_PLAYER_DATA)
            {
                i--;
            }
            else
            { 
                m->activePlayers[i] = m->playerData[m->chosenPlayer];
                adjustPlayerArr(m, m->chosenPlayer);
            }

            iClear(0, 0, CONSOLE_WIDTH, CONSOLE_HEIGHT);
        }
        newGame(m);
    }
    else
        errorNav(m);
}

/**
 * Displays the chosen players for the game
 * @param m A pointer to the game structure containing the game data
 * @return void
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

    printf("INITIALIZING PLAYERS...");
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

        if (i % 3 == 2 || i == m->playerCount - 1)
            printf("\n\n");
    }
}

/**
 * Displays the players who have not yet been chosen
 * @param m A pointer to the game structure containing the game data
 * @param playersChosen Amount of players already chosen
 * @return void
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

    if (m->nav.selected.x == 0 && m->nav.selected.y == 0)
        m->chosenPlayer = -1;
    else
        m->chosenPlayer = searchPlayer(selectPlayerOptions[m->nav.selected.y][m->nav.selected.x], m->playerData);
}

/**
 * Adjusts the player array by removing the chosen player and adjusting the position of the succeeding players
 * @param m A pointer to the game structure containing the game data
 * @param selectedPlayers Index of the selected player who will play the game
 * @return void
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
    bool duplicateExist = false;
    bool invalidUsername = false;
    int i = 0;

    iClear(0, 0, CONSOLE_WIDTH, CONSOLE_HEIGHT);
    printf("+------------------------------------------------------+\n");
    printf("|                     ADD NEW PLAYER                   |\n");
    printf("+------------------------------------------------------+\n");
    printf("  Enter username (max 36 chars):\n");
    getCursorPosition(&m->nav.cursorPos.x, &m->nav.cursorPos.y);
    do
    {
        printf("  > ");
        setColor(MAGENTA);
        scanf("%s", temp);
        setColor(WHITE);
        
        if (strlen(temp) > 36)
        {   
            setColor(RED);
            printf("  Username can only be below or equal to 36 characters!");
            setColor(WHITE);
            invalidUsername = true;
        }
        else
        {
            if ((searchPlayer(temp, m->activePlayers) != -1) || (searchPlayer(temp, m->playerData)) != -1)
                duplicateExist = true;

            if (duplicateExist)
            {
                setColor(RED);
                printf("  Username already exists!");
                setColor(WHITE);
            }
        }
        
        if (duplicateExist || invalidUsername)
            iClear(m->nav.cursorPos.x, m->nav.cursorPos.y, CONSOLE_WIDTH, 1);
    } while (duplicateExist || invalidUsername);

    setColor(GREEN);
    printf("  Player successfully added!");
    setColor(WHITE);

    strcpy(newPlayer, temp);
    m->totalPlayers++;

    do
    {
        if (strcmp(m->playerData[i].username, "") == 0)
        {
            strcpy(m->playerData[i].username, newPlayer);
            foundEmptyPlayer = true;
        }

        i++;
    } while (i < m->totalPlayers && !foundEmptyPlayer);

    playerFile = fopen("players.txt", "a");

    fprintf(playerFile, "\n%s,0,0", newPlayer);

    fclose(playerFile);

    pauseScreen(3.0);
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

/**
 * Searches the player list if a player already exist
 * @param currentPlayer The player being searched for
 * @param playerList The player list being search through
 * @return Player's index if the player was found
 * @return -1 If the player wasn't found
 */
int searchPlayer(char *currentPlayer, Player playerList[])
{
    int i = 0;
    int playerIndex = -1;
    bool playerFound = false;
    bool endOfPlayerList = false;

    do
    {
        if (strcmp(currentPlayer, playerList[i].username) == 0)
        {
            playerIndex = i;
            playerFound = true;
        }

        i++;

        if (strcmp(playerList[i].username, "") == 0)
            endOfPlayerList = true;
    } while (!playerFound && !endOfPlayerList);

    return playerIndex;
}

#endif // PLAYER_C;