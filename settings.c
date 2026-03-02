#ifndef SETTINGS_C
#define SETTINGS_C

#include <stdio.h>
#include <stdbool.h>

#include "defs.h"

/**
 * Settings menu of Mantis where players can modify game configuration
 * @param m A pointer to the game structure containing the game data
 * @return The function updates 
 */
void gameSettings(Game *m)
{
    int option;

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
        case 1: m->settings.winningPoints = setWinningPoints(); break;
        case 2: m->settings.shuffleSeed = setShuffleSeed(); break;
        case 3: m->settings = defaultSettings(); printf("Default settings loaded!\n"); break;
        case 0: mainMenu(m); break;
        }

        saveGameSettings(m);
    } while (option != 0);
}

/**
 * Sets the amount of points required to win Mantis
 * @return The player's chosen amount of points
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
 * @return The player's chosen shuffle seed
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
 * Sets the game configuration of Mantis to its default setting (20 WIN POINTS, RANDOM SHUFFLE SEED)
 * @return Default settings of Mantis
 */
Config defaultSettings()
{
    Config d;

    d.winningPoints = DEFAULT_WIN_POINTS; 
    d.shuffleSeed = RANDOM;

    return d;
}

/**
 * Saves the game settings of mantis to "settings.txt"
 * @param m A pointer to the game structure containing the game data
 * @return The function doesn't return anything
*/
void saveGameSettings(Game *m)
{
    FILE *settingsFile;

    settingsFile = fopen("settings.txt", "w");
    
    if (m->settings.winningPoints < 20)
    {
        m->settings.winningPoints = 20;
    }

    fprintf(settingsFile, "%d\n%d", m->settings.winningPoints, m->settings.shuffleSeed);

    fclose(settingsFile);
}


#endif // SETTINGS_C;
