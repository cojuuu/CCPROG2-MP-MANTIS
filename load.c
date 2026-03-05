/**
 * Description : Contains the functions that handles the file loading of Mantis
 * Author/s : De Dios, Justin Marco C.
 *            Ocampo, Kysha Denise D.
 *  Section : S12A & S22A
 *  Last Modified : 03-05-2026
 */

#ifndef LOAD_C 
#define LOAD_C 

#include <stdio.h>
#include <stdbool.h>

#include "defs.h"

/**
 * Loads player data from the "players.txt" file and storing them in m->playerData[]
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

    // Open player data file
    playerFile = fopen("players.txt", "r");

    // Checks if file was opened successfully
    if (playerFile == NULL)
    {
        fprintf(stderr, "player.txt not found!");
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
                printf("Error cannot read player data!\n");
                loadSuccess = false;
            }
        } while (!feof(playerFile) && loadSuccess == true);
    }

    m->totalPlayers = i;    

    // Close player data file
    fclose(playerFile);

    return loadSuccess;
}

/**
 * Loads card data from the "mantis.txt" file to m->drawPile.cards
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

    // Open card data file
    cardFile = fopen("mantis.txt", "r");

    // Checks if file was opened successfully
    if (cardFile == NULL)
    {
        fprintf(stderr, "mantis.txt not found!");
        loadSuccess = false;
    }

    if (loadSuccess)
    {
        do
        {
            // Parses player data into respective variables
            buffer = fscanf(cardFile, "%c | %c%c%c %d\n", 
                        &m->drawPile.cards[i].front, 
                        &m->drawPile.cards[i].back[0], &m->drawPile.cards[i].back[1], &m->drawPile.cards[i].back[2], 
                        &m->drawPile.cards[i].points);
            
            if (buffer == 5)
                i++;
            
            if (buffer != 5 && !feof(cardFile))
            {
                printf("Error cannot read card data!\n");
                loadSuccess = false;
            }

        } while (!feof(cardFile) && loadSuccess == true);
    }
    
    if (i != MAX_CARDS)
    {
        printf("Missing cards!\n");
        loadSuccess = false;
    }
    else
        m->drawPile.cardCount = MAX_CARDS;

    // Close card data file
    fclose(cardFile);

    return loadSuccess;
}

/**
 * Loads Mantis settings from the "settings.txt" file to m->settings
 * @param m A pointer to the game structure containing the game data
 * @return True If the load was successful
 * @return False Otherwise
 */
bool loadSettings(Game *m)
{
    FILE *settingsFile;
    bool loadSuccess = true;
    int buffer = 0;

    // Open card data file
    settingsFile = fopen("settings.txt", "r");

    // Checks if file was opened successfully
    if (settingsFile == NULL)
    {
        fprintf(stderr, "mantis.txt not found!");
        loadSuccess = false;
    }

    if (loadSuccess)
    {
        // Parses player data into respective variables
        buffer = fscanf(settingsFile, "%d\n%d", &m->settings.winningPoints, &m->settings.shuffleSeed);
        if (m->settings.shuffleSeed == RANDOM)
        {
            initRandom();
            m->settings.shuffleSeed = randomInt();
        }

        if (buffer != 2)
        {
            printf("Error cannot read card data!\n");
            loadSuccess = false;
        }  
    }

    // Close card data file
    fclose(settingsFile);

    return loadSuccess;
}

#endif // LOAD_C;