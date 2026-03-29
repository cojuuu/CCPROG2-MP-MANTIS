/**
 * Description : Contains the functions that handles the file loading/updating of Mantis
 * Author/s : De Dios, Justin Marco C.
 *            Ocampo, Kysha Denise D.
 *  Section : S12A & S22A
 *  Last Modified : 03-29-2026
 */

#ifndef LOAD_C 
#define LOAD_C 

#include <stdio.h>
#include <stdbool.h>

#include "defs.h"

/**
 * Loads player data from the "players.txt" file
 * @param m A pointer to the game structure containing the game data
 * @return true If the load was successful
 * @return false Otherwise
 */
bool loadPlayerData(Game *m)
{
    FILE *playerFile;
    bool loadSuccess = true;
    int buffer = 0;
    int i = 0;

    playerFile = fopen("players.txt", "r");

    if (playerFile == NULL)
    {
        printError();
        setColor(RED);
        printf("\nplayer.txt not found!\n");
        setColor(WHITE);
        loadSuccess = false;
    }

    if (loadSuccess)
    {
        do
        {
            // Parses player data into respective variables
            buffer = fscanf(playerFile, "%36[^,],%d,%d\n", 
                m->playerData[i].username, 
               &m->playerData[i].wins, 
               &m->playerData[i].totalScore);

            if (buffer == 3)
                i++;
            
            if (buffer != 3 && !feof(playerFile))
            {
                printError();
                setColor(RED);
                printf("\nError cannot read player data!\n");
                setColor(WHITE);
                loadSuccess = false;
            }
        } while (!feof(playerFile) && loadSuccess == true);

        m->totalPlayers = i;
    }
    fclose(playerFile);

    return loadSuccess;
}

/**
 * Loads card data from the "mantis.txt" file
 * @param m A pointer to the game structure
 * @return True If the load was successful
 * @return False Otherwise
 */
bool loadCards(Game *m)
{
    FILE *cardFile;
    bool loadSuccess = true;
    int buffer = 0;
    int i = 0;

    cardFile = fopen("mantis.txt", "r");

    if (cardFile == NULL)
    {
        printError();
        setColor(RED);
        printf("\nmantis.txt not found!\n");
        setColor(WHITE);
        loadSuccess = false;
    }

    if (loadSuccess)
    {
        do
        {
            buffer = fscanf(cardFile, "%c | %c%c%c %d\n", 
                        &m->drawPile.cards[i].front, 
                        &m->drawPile.cards[i].back[0], &m->drawPile.cards[i].back[1], &m->drawPile.cards[i].back[2], 
                        &m->drawPile.cards[i].points);
            
            if (buffer == 5)
                i++;
            
            if (buffer != 5 && !feof(cardFile))
            {
                printError();
                setColor(RED);
                printf("\nError cannot read card data!\n");
                setColor(WHITE);
                loadSuccess = false;
            }

        } while (!feof(cardFile) && loadSuccess);

        if (i != MAX_CARDS && loadSuccess)
        {
            printError();
            setColor(RED);
            printf("\nMissing cards!\n");
            setColor(WHITE);
            loadSuccess = false;
        }
        else
            m->drawPile.cardCount = MAX_CARDS;
    }
    fclose(cardFile);

    return loadSuccess;
}

/**
 * Loads Mantis settings from the "settings.txt" file
 * @param m A pointer to the game structure containing the game data
 * @return True If the load was successful
 * @return False Otherwise
 */
bool loadSettings(Game *m)
{
    FILE *settingsFile;
    bool loadSuccess = true;
    int buffer = 0;

    settingsFile = fopen("settings.txt", "r");

    if (settingsFile == NULL)
    {
        printError();
        setColor(RED);
        printf("\nsettings.txt not found!\n");
        setColor(WHITE);
        loadSuccess = false;
    }

    if (loadSuccess)
    {
        buffer = fscanf(settingsFile, "%d\n%d", &m->settings.winningPoints, &m->settings.shuffleSeed);
    
        if (buffer != 2)
        {
            printError();
            setColor(RED);
            printf("\nError cannot read settings\n");
            setColor(WHITE);
            loadSuccess = false;
        }  
    }

    fclose(settingsFile);

    return loadSuccess;
}

/**
 * Updates "player.txt" with the updated player stats
 * @param currentDeck The deck being checked
 * @return void
 */
void updatePlayerData(Game *g)
{
    FILE *playerFile;
    int i;

    for (i = 0; i < g->playerCount; i++)
    {
        if (g->activePlayers[i].scorePile.totalPoints >= g->settings.winningPoints)
            g->activePlayers[i].wins++;
    }

    for (i = 0; i < g->playerCount; i++)
        g->activePlayers[i].totalScore += g->activePlayers[i].scorePile.totalPoints;

    playerFile = fopen("players.txt", "w");

    for (i = 0; i < g->playerCount; i++)
        fprintf(playerFile ,"%s,%d,%d\n", g->activePlayers[i].username, g->activePlayers[i].wins, g->activePlayers[i].totalScore);

    for (i = 0; i < g->totalPlayers - g->playerCount; i++)
        fprintf(playerFile ,"%s,%d,%d\n", g->playerData[i].username, g->playerData[i].wins, g->playerData[i].totalScore);

    fclose(playerFile);
}

#endif // LOAD_C;