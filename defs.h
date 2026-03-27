/**
* Description : Header file for the CCPROG2 machine project
*               Contains constants, type definitions, structures,
*               and function prototypes used by the program
* Author/s : De Dios, Justin Marco C.
*            Ocampo, Kysha Denise D.
* Section : S12A & S22A
* Last Modified : 03-05-2026
*/

#ifndef DEFS_H
#define DEFS_H

#include <stdio.h>
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
#define MAX_CARDS 84
#define RANDOM -1
#define BY_SCORE 67
#define BY_WINS 69
#define STARTING_CARDS 4
#define NOT_FOUND -2
#define INCREMENT '+'
#define DECREMENT '-'
#define RED 'R'
#define WHITE 'O'
#define YELLOW 'Y'
#define GREEN 'G'
#define BLUE 'B'
#define CYAN 'I'
#define PURPLE 'V'
#define MAGENTA 'M'
#define GRAY 'A'
#define CONSOLE_WIDTH 100
#define CONSOLE_HEIGHT 40
#define BIG 101
#define SMALL 102
#define FRONT 103
#define BACK 104
#define ACTIVE 105
#define INACTIVE 106

#define MANTIS_LOGO_HEIGHT 8
#define MANTIS_LOGO_WIDTH 65
#define SETTINGS_MENU_HEIGHT 25

#define ENTER_KEY 13

#define MAX_OPT_COL 3

typedef char String36[STR36];
typedef char String100[STR100];
typedef char Color;

/**
 * Represents a card
 */
typedef struct 
{
    Color front;   // Front color of card
    Color back[3]; // Back color of card
    int points;    // Point value of card
} Card;

/**
 * Represents the color count
 */
typedef struct
{
    int white, red, blue, green, yellow, cyan, purple;
} Counter;

typedef struct
{
    int x, y;
} Cord;


/**
 * Represents a deck
 */
typedef struct 
{
    Card cards[MAX_CARDS]; // Cards in the deck
    int cardCount;         // Cards left in the deck
    Counter colorCount;    // Amount of cards for each color
    int totalScore;        // Total score in the deck
} Deck;

/**
 * Represents a player
 */
typedef struct
{
    String36 username;  // Username of the player
    int wins;           // Total wins of the player
    int totalScore;     // Total score of the player

    Deck tank;          // Tank deck of the player
    Deck scorePile;     // Score pile of the player
} Player;

/**
 * Represents the game settings of Mantis
 */
typedef struct 
{
    int winningPoints; // Points required to win Mantis
    int shuffleSeed;   // Shuffle seed for shuffling cards
} Config;

typedef struct 
{
    int x;
    int y;

    int kbInput;
    int selectedOption;

    Cord cursorPos;
    Cord selected;

    bool optionSelected;
} Navigator;


/**
 * Represents the game structure of Mantis
 */
typedef struct
{
    int playerCount;  // Amount of players who will play
    int totalPlayers; // Total amount of players in "players.txt"

    int currentPlayer;   // Index of the player with the current turn
    int winner[MAX_PLAYERS]; // Index of the player/s who won the game
    int winnerCount;     // Amount of winners
    int stolenPlayer;    // Index of the player who got stolen from

    int sameColorPoints; // Total points of the cards with the same color as drawn card
    int sameColorCount;  // Amount of cards with the same color as drawn card

    int chosenPlayer;

    bool gameOver; // Flag indicating if the game is over
    bool foundWinner; // Flag indicating if the winner was found
    bool tieGame; // Flag indicating if it is a tie game

    Player activePlayers[MAX_PLAYERS];  // Players who will play the game
    Player playerData[MAX_PLAYER_DATA]; // Players from "players.txt"

    Deck drawPile; // Draw pile of Mantis
    Card drawnCard; // Drawn card from draw pile

    Config settings; // Game configuration of Mantis

    Navigator nav;
} Game;

// Menu Function Prototypes
void mainMenu(Game *m);
void askOption(int *option, int min, int max);
void printLogo();
void interactiveMenu(Navigator *nav, String36 navOptions[], int optionCount);
void interactiveMenu2D(Navigator *nav, String36 navOptions[][MAX_OPT_COL], int rowOptCount, int colOptCount);

// Deck Function Prototypes
Card drawCard(Game *m);
void adjustDeck(Deck *deck, int removedCardIndex);
void colorCount(Deck *currentDeck, Color currentCard, char mode);
int emptyCardIndex(Deck currentDeck);
Card emptyCard();
void distributeCards(Game *m);
void displayTopDeck(Game *m);
void displayCard(Card currentCard, int cardSize, int cardSide);
void displayFrontSideDeck(Deck currentDeck, int cardSize);
void checkSameColor(Game *m, Deck tank);
void revealCard(Card drawnCard);
void printEmoticon(Color currentColor);

// Game Function Prototypes
void newGame(Game *m);
void setUpGame(Game *m);
void gameLoop(Game *m);
void checkWinner(Game *m);
void checkSpecialWinner(Game *g);

// Player Function Prototypes
void selectPlayers(Game *m);
void displayChosenPlayers(Game *m);
void displayAvailPlayers(Game *m, int playersChosen);
void adjustPlayerArr(Game *m, int selectedPlayer);
void addNewPlayer(Game *m);
bool playerFound(Game *m, String36 newPlayer);
Player emptyPlayer();
void addToScorePile(Player *currentPlayer, Card drawnCard);
void addToTank(Player *currentPlayer, Card drawnCard);
void stealTank(Player *currentPlayer, Player *stolenPlayer, Color drawnCard);
void calculateScore(Player *currentPlayer);
void displayPlayerState(Game *m, int playerType);
void displayWinner(Game *g);
void promptPlayerMove(Game *m);
void tryToScore(Game *m);
void tryToSteal(Game *m);
void promptSteal(Game *m);
void updatePlayerData(Game *g);
int searchPlayer(String36 currentPlayer, Player playerList[]);

// Leaderboard Function Prototypes
void leaderBoard(Game *m);
void sortPlayers(Game *m, int sortType);
void displayLeaderboard(Game *m, int displayType);
void displayPodium(Game *m, int displayType);

// Load Function Prototypes
bool loadPlayerData(Game *m);
bool loadCards(Game *m);
bool loadSettings(Game *m);

// Settings Function Prototypes
void gameSettings(Game *m);
void setWinningPoints(Game *m);
void setShuffleSeed(Game *m);
void saveGameSettings(Game *m);
Config defaultSettings();

// Random Function Prototypes
void initRandom();
int randomInt();
void shuffle(void *array, size_t n, size_t elem_size, unsigned int seed);

// Interface Function Prototypes
void iMoveCursor(int x, int y);
void iClear(int x, int y, int width, int height);
void iHideCursor();
void iShowCursor();
void iSetColor(int color);
void setColor(Color currentColor);
void pauseScreen(double seconds);
void waitEnter(char *message);
void getCursorPosition(int *x, int *y);

#endif // DEFS_H;
