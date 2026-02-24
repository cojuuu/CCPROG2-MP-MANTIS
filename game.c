#ifndef GAME_C 
#define GAME_C 

#include <stdio.h>

#include "defs.h"

/**
 * Starts a new game of Mantis from player selection to the actual game flow
 * @param m A pointer to the game structure containing the game data
 * @return The function doesn't return anything
 */
void newGame(Game *m)
{
    // Ask how many players will play
    printf("How many players?\n");
    askOption(&m->playerCount, MIN_PLAYERS, MAX_PLAYERS);

    // Select Players
    selectPlayers(m);

    // Game Loop
    loadCards(m);
}

void setUpGame(Game *m)
{
    
}

#endif // GAME_C;

