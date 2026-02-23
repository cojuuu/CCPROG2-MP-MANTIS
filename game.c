#ifndef GAME_C 
#define GAME_C 

#include <stdio.h>

#include "defs.h"

/**
 * Starts a new game of Mantis from player selection to the actual game flow
 * @return The function doesn't return anything
 */
void newGame()
{
    Player activePlayers[MAX_PLAYERS], availPlayers[MAX_PLAYER_DATA];
    int playerCount;
    Card decks[MAX_CARDS];

    // Ask how many players will play
    printf("How many players?\n");
    askOption(&playerCount, MIN_PLAYERS, MAX_PLAYERS);

    // Select Players
    selectPlayers(activePlayers, availPlayers, playerCount);

    // Game Loop
    loadCards(decks);

    for (int i = 0; i < MAX_CARDS; i++)
        printf("%c | %c%c%c %d\n", decks[i].front.color, decks[i].back[0].color, decks[i].back[1].color, decks[i].back[2].color, decks[i].points);
}

#endif // GAME_C;

