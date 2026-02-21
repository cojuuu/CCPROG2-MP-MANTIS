/**
* Description : <short description of the file>
* Author/s : De Dios, Justin Marco C.
*            Ocampo, Kysha Denise D.
* Section : S12A & S22A
* Last Modified : 02-01-2026
*/

#ifndef DEFS_H
#define DEFS_H

#include <stdbool.h>

#define STR36 37
#define MIN_PLAYERS 3
#define MAX_PLAYERS 6
#define MAX_PLAYER_DATA 50

typedef char String36[STR36];

/**
 * Represents a player
 */
typedef struct
{
    String36 username; // Username of the player
    int wins;          // Total wins of the player
    int score;         // Highest score of the player
} Player;

// Menu Function Prototypes
void mainMenu(int *option);
void askOption(int *option, int min, int max);

// Game Function Prototypes
void newGame();
void selectPlayers(Player selectedPlayers[], Player availPlayers[], int playerCount);
void displayChosenPlayers(Player selectedPlayers[], int playerCount);
void displayAvailPlayers(Player availPlayers[], Player selectedPlayers[], int totalPlayers);
void adjustPlayerArr(Player availPlayers[], int selectedPlayer, int totalPlayers);
void addPlayer(Player availPlayers[], int *totalPlayers);
Player emptyPlayer();

// Leaderboard Function Prototypes
void leaderBoard();

// Load Function Prototypes
bool loadPlayerData(Player playerData[], int *totalPlayer);

// Settings Function Prototypes
void gameSettings();

#endif // DEFS_H;