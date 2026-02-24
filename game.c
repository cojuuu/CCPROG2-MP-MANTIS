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
    setUpGame(m);
    displayTopDeck(m);
}

/**
 * Loads the settings and cards, shuffles the Draw Pile, and deals out the cards to the players
 * @param m A pointer to the game structure containing the game data
 * @return The function doesn't return anything
 */
void setUpGame(Game *m)
{
    loadSettings(m);
    if (m->settings.shuffleSeed == RANDOM)
    {
        initRandom();
        m->settings.shuffleSeed = randomInt();
    }

    loadCards(m);
    shuffle(m->drawPile, MAX_CARDS, sizeof(Card), m->settings.shuffleSeed);

    initializePlayer(m);
    distributeCards(m);
    checkColorCount(m);
    displayCards(m);
}

void distributeCards(Game *m)
{
    int i, j;

    for (i = 0; i < m->playerCount; i++)
    {
        for (j = 0; j < STARTING_CARDS; j++)
        {
            m->activePlayers[i].tank[j] = drawCard(m);
            m->activePlayers[i].cardCount++;
        }
    }
}

Card drawCard(Game *m)
{
    Card drawnCard;
    int i;

    drawnCard = m->drawPile[0];
    m->cardsInDeck--;

    for (i = 0; i < m->cardsInDeck; i++)
    {
        m->drawPile[i] = m->drawPile[i + 1];
    }

    return drawnCard;
}

void displayCards(Game *m)
{
    int i;

    for (i = 0; i < m->playerCount; i++)
    {
        printf("P%d => [ R: %d | O:%d | Y: %d | G:%d | B:%d | I:%d | V:%d ] // %d\n", i + 1,
            m->activePlayers[i].count.red, m->activePlayers[i].count.white, 
            m->activePlayers[i].count.yellow, m->activePlayers[i].count.green, 
            m->activePlayers[i].count.blue, m->activePlayers[i].count.cyan, 
            m->activePlayers[i].count.purple, m->activePlayers[i].currentScore);
    }
}

void initializePlayer(Game *m)
{
    int i, j;

    
    for (i = 0; i < m->playerCount; i++)
    {
        // Empty color count
        m->activePlayers[i].count.white = 0;
        m->activePlayers[i].count.red = 0;
        m->activePlayers[i].count.blue = 0;
        m->activePlayers[i].count.green = 0;
        m->activePlayers[i].count.yellow = 0;
        m->activePlayers[i].count.cyan = 0;
        m->activePlayers[i].count.purple = 0;

        // Empty card count
        m->activePlayers[i].cardCount = 0;

        // Empty current score
        m->activePlayers[i].currentScore = 0;

        for (j = 0; j < MAX_CARDS; j++)
        {
            // Empty tank
            m->activePlayers[i].tank[j] = emptyCard();
        }
    }
}

Card emptyCard()
{
    Card e = {'\0', {'\0', '\0', '\0'}, 0};

    return e;
}

void checkColorCount(Game *m)
{
    int i, j;

    for (i = 0; i < m->playerCount; i++)
    {
        for (j = 0; j < m->activePlayers[i].cardCount; j++)
        {
            switch (m->activePlayers[i].tank[j].front)
            {
                case 'R': m->activePlayers[i].count.red++; break;
                case 'O': m->activePlayers[i].count.white++; break;
                case 'Y': m->activePlayers[i].count.yellow++; break;
                case 'G': m->activePlayers[i].count.green++; break;
                case 'B': m->activePlayers[i].count.blue++; break;
                case 'I': m->activePlayers[i].count.cyan++; break;
                case 'V': m->activePlayers[i].count.purple++; break;
            }
        }
    }
}

void displayTopDeck(Game *m)
{
    printf("\nTop deck: %c%c%c (%d cards remaining in deck)\n", 
        m->drawPile[0].back[0], m->drawPile[0].back[1], m->drawPile[0].back[2], m->cardsInDeck);
}

#endif // GAME_C;

