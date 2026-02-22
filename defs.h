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
#define STR100 101
#define MIN_PLAYERS 3
#define MAX_PLAYERS 6
#define MAX_PLAYER_DATA 50
#define TOP_10 10
#define DEFAULT_WIN_POINTS 20
#define MAX_WIN_POINTS 100
#define MIN_SHUFFLE_SEED 0
#define MAX_SHUFFLE_SEED 99

typedef char String36[STR36];
typedef char String100[STR100];

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
void mainMenu();
void askOption(int *option, int min, int max);

// Game Function Prototypes
void newGame();
void selectPlayers(Player selectedPlayers[], Player availPlayers[], int playerCount);
void displayChosenPlayers(Player selectedPlayers[], int playerCount);
void displayAvailPlayers(Player availPlayers[], int totalPlayers);
void adjustPlayerArr(Player availPlayers[], int selectedPlayer, int totalPlayers);
void addPlayer(Player availPlayers[], Player selectedPlayers[], int *totalPlayers);
bool playerFound(Player availPlayers[], String36 newPlayer, int totalPlayers);
Player emptyPlayer();

// Leaderboard Function Prototypes
void leaderBoard();
void displayLeaderBoardMenu(int *option);
void leaderBoardWins(Player playerData[], int totalPlayerData);
void leaderBoardScore(Player playerData[], int totalPlayerData);

// Load Function Prototypes
bool loadPlayerData(Player playerData[], int *totalPlayer);

// Settings Function Prototypes
void gameSettings();
int setWinningPoints();
int setShuffleSeed();
void saveGameSettings(int winningPoints, int shuffleSeed);

// Random Function Prototypes
void initRandom();
int randomInt();
void shuffle(void *array, size_t n, size_t elem_size, unsigned int seed);

#endif // DEFS_H;
