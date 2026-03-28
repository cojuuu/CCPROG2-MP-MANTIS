/**
 * Description : Contains the functions that handles the settings of Mantis
 * Author/s : De Dios, Justin Marco C.
 *            Ocampo, Kysha Denise D.
 *  Section : S12A & S22A
 *  Last Modified : 03-27-2026
 */

#ifndef SETTINGS_C
#define SETTINGS_C

#include <stdio.h>
#include <stdbool.h>

#include "defs.h"

/**
 * Settings menu of Mantis where players can modify game configuration
 * @param m A pointer to the game structure containing the game data
 * @return void
 */
void gameSettings(Game *m)
{
    String36 settingOptions[] = {"S E T  W I N N I N G  P O I N T S", "S E T  S H U F F L E  S E E D", "R E S T O R E  T O  D E F A U L T", "B A C K"};
    
    printLogo();
    printf("\nSETTINGS\n");
    loadSettings(m);
    printf("+-----------------------------------------------------------+\n");
    printf("|  Winning Points          %-33d|\n", m->settings.winningPoints);
    if (m->settings.shuffleSeed == RANDOM)
        printf("|  Shuffle Seed            %-33s|\n", "RANDOM");
    else
        printf("|  Shuffle Seed            %-33d|\n", m->settings.shuffleSeed);
    printf("+-----------------------------------------------------------+\n");
    interactiveMenu1D(&m->nav, settingOptions, 4);

    switch(m->nav.selectedOption)
    {
        case 0: setWinningPoints(m); break;
        case 1: setShuffleSeed(m); break;
        case 2: 
            m->settings = defaultSettings(); 
            saveGameSettings(m); 
            iClear(0, 0, CONSOLE_WIDTH, CONSOLE_HEIGHT); 
            gameSettings(m); 
            break;
        case 3: 
            saveGameSettings(m); 
            iClear(0, 0, CONSOLE_WIDTH, CONSOLE_HEIGHT); 
            mainMenu(m); 
            break;
    }
}

/**
 * Sets the winning points of Mantis
 * @param m A pointer to the game structure containing the game data
 * @return void
 */
void setWinningPoints(Game *m)
{
    int i;

    getCursorPosition(&m->nav.x, &m->nav.y);
    do
    {
        setColor(MAGENTA);
        printf("\n  >> S E T  W I N N I N G  P O I N T S: ");
        scanf("%d", &m->settings.winningPoints); 

        if (m->settings.winningPoints < DEFAULT_WIN_POINTS || m->settings.winningPoints > MAX_WIN_POINTS)
        {
            setColor(RED);
            printf("  Minimum of 20 win points. Maximum of 100 win points. Please enter another value!");
            iClear(m->nav.x, m->nav.y, CONSOLE_WIDTH, 2);
        }
    } while (m->settings.winningPoints < DEFAULT_WIN_POINTS || m->settings.winningPoints > MAX_WIN_POINTS);

    getCursorPosition(&m->nav.x, &m->nav.y);
    iClear(m->nav.x, m->nav.y, CONSOLE_WIDTH, 1);
    setColor(GREEN);
    printf("   Winning points was successfully changed!\n"); 
    setColor(WHITE);

    printf("\n   Returning to settings menu");
    for (i = 0; i < 3; i++)
    {
        printf(".");
        pauseScreen(2.0);
    }
    iClear(0, 0, CONSOLE_WIDTH, CONSOLE_HEIGHT);
    saveGameSettings(m);
    gameSettings(m);
}

/**
 * Sets the shuffle seed of Mantis
 * @param m A pointer to the game structure containing the game data
 * @return void
 */
void setShuffleSeed(Game *m)
{
    int i;

    getCursorPosition(&m->nav.x, &m->nav.y);
    do
    {
        setColor(MAGENTA);
        printf("\n  >> S E T  S H U F F L E  S E E D: ");
        scanf("%d", &m->settings.shuffleSeed); 

        if (m->settings.shuffleSeed < MIN_SHUFFLE_SEED || m->settings.shuffleSeed > MAX_SHUFFLE_SEED)
        {
            setColor(RED);
            printf("   Please input a number ranging from 0 to 99!\n");
            iClear(m->nav.x, m->nav.y, 100, 2);
        }
    } while (m->settings.shuffleSeed < MIN_SHUFFLE_SEED || m->settings.shuffleSeed > MAX_SHUFFLE_SEED);

    getCursorPosition(&m->nav.x, &m->nav.y);
    iClear(m->nav.x, m->nav.y, 100, 1);
    setColor(GREEN);
    printf("   Shuffle seed was successfully changed!\n"); 
    setColor(WHITE);

    printf("\n   Returning to settings menu");
    for (i = 0; i < 3; i++)
    {
        printf(".");
        pauseScreen(1.0);
    }
    iClear(0, 0, 100, 50);
    saveGameSettings(m);
    gameSettings(m);
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
 * @return void
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