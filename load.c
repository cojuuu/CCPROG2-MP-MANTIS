#ifndef LOAD_C 
#define LOAD_C 

#include <stdio.h>
#include <stdbool.h>

#include "defs.h"

/**
 * Loads player data from the "players.txt" file
 * @param playerData Where the extracted data will be stored
 * @param totalPlayers Total players loaded from the file
 * @return true If the load was successful
 * @return false Otherwise
 */
bool loadPlayerData(Player playerData[], int *totalPlayer)
{
    FILE *playerFile;
    bool loadSuccess = true;
    int buffer = 0;
    int i;

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
                playerData[*totalPlayer].username, 
               &playerData[*totalPlayer].wins, 
               &playerData[*totalPlayer].score);

            if (buffer == 3)
            {
                *totalPlayer += 1;
            }
            
            if (buffer != 3 && !feof(playerFile))
            {
                printf("Error cannot read player data!\n");
                loadSuccess = false;
            }
        } while (!feof(playerFile) && loadSuccess == true);
    }

    // Close player data file
    fclose(playerFile);

    // Initialize the rest of the playerData variable to default values
    for (i = *totalPlayer; i < MAX_PLAYER_DATA; i++)
        playerData[i] = emptyPlayer();

    return loadSuccess;
}

/**
 * Loads card data from the "mantis.txt" file
 * @param decks Where the extracted card data will be stored
 * @return true If the load was successful
 * @return false Otherwise
 */
bool loadCards(Card decks[])
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
                        &decks[i].front.color, &decks[i].back[0].color, &decks[i].back[1].color, &decks[i].back[2].color, &decks[i].points);
            
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

    // Close card data file
    fclose(cardFile);

    return loadSuccess;
}

#endif // LOAD_C;