/**
 * Description : Contains the functions that handles the settings of Mantis
 * Author/s : De Dios, Justin Marco C.
 *            Ocampo, Kysha Denise D.
 *  Section : S12A & S22A
 *  Last Modified : 03-05-2026
 */

#ifndef SETTINGS_C
#define SETTINGS_C

#include <stdio.h>
#include <stdbool.h>

#include "defs.h"

/**
 * Settings menu of Mantis where players can modify game configuration
 * @param m A pointer to the game structure containing the game data
 */
void gameSettings(Game *m)
{
    char *settingOptions[] = {"S E T  W I N N I N G  P O I N T S\n", "S E T  S H U F F L E  S E E D\n", "R E S T O R E  T O  D E F A U L T\n", "B A C K\n"};
    int selectedOption = 0;
    int input;
    bool optionSelected = false;

    do
    {
        printLogo();
        printf("\nSETTINGS\n\n");

        for (int i = 0; i < 4; i++)
        {
            if (i == selectedOption)
            {
                iSetColor(6);
                printf("\n\t%s\n", settingOptions[i]);
                iSetColor(0);
            }
            else
            {
                printf("%s\n", settingOptions[i]);
            }
        }

        input = getch();

        switch(input)
        {
            case 'w': 
            case 'W': selectedOption-= 1; break;
            case 's': 
            case 'S': selectedOption+= 1; break;
            case 13: optionSelected = true; break; // enter key
        }

        if (selectedOption > 3)
        {
            selectedOption = 0;
        }
        else if (selectedOption < 0)
        {
            selectedOption = 3;
        }

            iClear(0, 0, CONSOLE_WIDTH, CONSOLE_HEIGHT);
    } while (!optionSelected);

    switch(selectedOption)
    {
        case 0: m->settings.winningPoints = setWinningPoints(); break;
        case 1: m->settings.shuffleSeed = setShuffleSeed(); break;
        case 2: m->settings = defaultSettings(); printf("Default settings loaded!\n"); break;
        case 3: mainMenu(m); break;
    }
     saveGameSettings(m);
}

/**
 * Sets the winning points of Mantis
 * @return The player's chosen winning points
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