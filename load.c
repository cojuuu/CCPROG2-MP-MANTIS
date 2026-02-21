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

    return loadSuccess;
}

#endif // LOAD_C;
