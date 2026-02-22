#ifndef SETTINGS_C
#define SETTINGS_C

#include <stdio.h>
#include <stdbool.h>

#include "defs.h"

/**
 * Menu where players can modify the game settings of Mantis
 * @return The function doesn't return anything
 */
void gameSettings()
{
    int option;
    int winningPoints, shuffleSeed; 

    do
    {
        printf("Settings\n");
        printf("  [1] Set Winning Points\n");
        printf("  [2] Set Shuffle Seed\n");
        printf("  [3] Restore to default\n");
        printf("  [0] Back\n");

        askOption(&option, 0, 3);

        switch(option)
        {
        case 1: winningPoints = setWinningPoints(); break;
        case 2: shuffleSeed = setShuffleSeed(); break;
        case 3: winningPoints = DEFAULT_WIN_POINTS; shuffleSeed = randomInt(); break;
        case 0: mainMenu(); break;
        }

        saveGameSettings(winningPoints, shuffleSeed);
    } while (option != 0);
}

/**
 * Sets the winning points of Mantis
 * @return The player's desired winning points
 */
int setWinningPoints()
{
    int winningPoints;

    do
    {
        printf("Set Winning Points: ");
        scanf("%d", &winningPoints); 

        if (winningPoints < DEFAULT_WIN_POINTS || winningPoints > MAX_WIN_POINTS)
            printf("Minimum of 20 win points. Maximum of 100 win points. Please enter another value!\n");
    } while (winningPoints < DEFAULT_WIN_POINTS || winningPoints > MAX_WIN_POINTS);

    return winningPoints;
}

/**
 * Sets the shuffle seed of Mantis
 * @return The player's desired shuffle seed
 */
int setShuffleSeed()
{
    int shuffleSeed;

    do
    {
        printf("Set Shuffle Seed: ");
        scanf("%d", &shuffleSeed); 

        if (shuffleSeed < MIN_SHUFFLE_SEED || shuffleSeed > MAX_SHUFFLE_SEED)
            printf("Please input a number ranging from 0 to 99!\n");
    } while (shuffleSeed < MIN_SHUFFLE_SEED || shuffleSeed > MAX_SHUFFLE_SEED);

    return shuffleSeed;
}

/**
 * Saves the game settings of mantis
 * @param winningPoints The minimum number of points required to win the game
 * @param shuffleSeed Seed value used for shuffling
 * @return The function doesn't return anything
 */
void saveGameSettings(int winningPoints, int shuffleSeed)
{
    FILE *settingsFile;

    settingsFile = fopen("settings.txt", "w");
    
    fprintf(settingsFile, "%d\n", winningPoints);
    fprintf(settingsFile, "%d", shuffleSeed);

    fclose(settingsFile);
}

#endif // SETTINGS_C;
