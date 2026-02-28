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
    printf("How many players?\n");
    askOption(&m->playerCount, MIN_PLAYERS, MAX_PLAYERS);

    selectPlayers(m);
    setUpGame(m);
    displayTopDeck(m);
    gameFlow(m);
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
    shuffle(m->drawPile.cards, MAX_CARDS, sizeof(Card), m->settings.shuffleSeed);

    initializePlayer(m);
    distributeCards(m);
    displayTankCards(m);
}

void gameFlow(Game *m)
{
    int option;

    for (m->currentPlayer = 0; m->currentPlayer < m->playerCount; m->currentPlayer++)
    {
        promptPlayerMove(m->currentPlayer + 1, &option);

        switch(option)
        {
            case 1: tryToScore(m); break;
            case 2: tryToSteal(m); break;
        }

        displayTankCards(m);
        displayTopDeck(m);
    }
}

void tryToScore(Game *m)
{
    int emptyCardIndex;
    Card drawnCard;

    printf("Resolving turn for Player %d...\n", m->currentPlayer + 1);

    drawnCard = drawCard(m);
    printf("- Drawn card color reveal: %c (%d pt/s)!\n", drawnCard.front, drawnCard.points);

    countSameColor(m, drawnCard);

    emptyCardIndex = findEmptyCard(m);
    m->activePlayers[m->currentPlayer].tank.cards[emptyCardIndex] = drawnCard;
    m->activePlayers[m->currentPlayer].tank.cardCount++;

    if (m->sameColorCount > 0)
    {
        m->activePlayers[m->currentPlayer].scorePile += m->sameColorPoints + drawnCard.points;
        printf("- Player %d has (%d) %c card/s worth a total of (%d) pts!\n", m->currentPlayer + 1, m->sameColorCount, drawnCard.front, m->sameColorPoints);
        printf("- +%d points to Player 1's score pile!\n", m->sameColorPoints + drawnCard.points);
    }
    else
    {
        printf("- Player %d has no %c cards...\n", m->currentPlayer + 1, drawnCard.front);
        printf("- Adding drawn card to Player 1's Tank\n");
        modifyColorCount(m, drawnCard.front, INCREMENT);
    }
}

void tryToSteal(Game *m)
{

}

void distributeCards(Game *m)
{
    int i;

    for (m->currentPlayer = 0; m->currentPlayer < m->playerCount; m->currentPlayer++)
    {
        for (i = 0; i < STARTING_CARDS; i++)
        {
            m->activePlayers[m->currentPlayer].tank.cards[i] = drawCard(m);
            m->activePlayers[m->currentPlayer].tank.cardCount++;
            modifyColorCount(m, m->activePlayers[m->currentPlayer].tank.cards[i].front, INCREMENT);
        }
    }
}

Card drawCard(Game *m)
{
    Card drawnCard;
    int i;

    drawnCard = m->drawPile.cards[0];
    m->drawPile.cardCount--;

    for (i = 0; i < m->drawPile.cardCount; i++)
    {
        m->drawPile.cards[i] = m->drawPile.cards[i + 1];
    }

    return drawnCard;
}

void displayTankCards(Game *m)
{
    int i;

    for (i = 0; i < m->playerCount; i++)
    {
        printf("P%d => [ R: %d | O:%d | Y: %d | G:%d | B:%d | I:%d | V:%d ] // %d\n", i + 1,
            m->activePlayers[i].nColor.red, m->activePlayers[i].nColor.white, 
            m->activePlayers[i].nColor.yellow, m->activePlayers[i].nColor.green, 
            m->activePlayers[i].nColor.blue, m->activePlayers[i].nColor.cyan, 
            m->activePlayers[i].nColor.purple, m->activePlayers[i].scorePile);
    }
}

void initializePlayer(Game *m)
{
    int i, j;

    
    for (i = 0; i < m->playerCount; i++)
    {
        // Empty color count
        m->activePlayers[i].nColor.white = 0;
        m->activePlayers[i].nColor.red = 0;
        m->activePlayers[i].nColor.blue = 0;
        m->activePlayers[i].nColor.green = 0;
        m->activePlayers[i].nColor.yellow = 0;
        m->activePlayers[i].nColor.cyan = 0;
        m->activePlayers[i].nColor.purple = 0;

        // Empty card count
        m->activePlayers[i].tank.cardCount = 0;

        // Empty current score
        m->activePlayers[i].scorePile = 0;

        for (j = 0; j < MAX_CARDS; j++)
        {
            // Empty tank
            m->activePlayers[i].tank.cards[j] = emptyCard();
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
        for (j = 0; j < m->activePlayers[i].tank.cardCount; j++)
        {
            switch (m->activePlayers[i].tank.cards[j].front)
            {
                case 'R': m->activePlayers[i].nColor.red++; break;
                case 'O': m->activePlayers[i].nColor.white++; break;
                case 'Y': m->activePlayers[i].nColor.yellow++; break;
                case 'G': m->activePlayers[i].nColor.green++; break;
                case 'B': m->activePlayers[i].nColor.blue++; break;
                case 'I': m->activePlayers[i].nColor.cyan++; break;
                case 'V': m->activePlayers[i].nColor.purple++; break;
            }
        }
    }
}

void modifyColorCount(Game *m, Color currentCard, char mode)
{
    if (mode == INCREMENT)
    {
        switch(currentCard)
        {
            case 'R': m->activePlayers[m->currentPlayer].nColor.red++; break;
            case 'O': m->activePlayers[m->currentPlayer].nColor.white++; break;
            case 'Y': m->activePlayers[m->currentPlayer].nColor.yellow++; break;
            case 'G': m->activePlayers[m->currentPlayer].nColor.green++; break;
            case 'B': m->activePlayers[m->currentPlayer].nColor.blue++; break;
            case 'I': m->activePlayers[m->currentPlayer].nColor.cyan++; break;
            case 'V': m->activePlayers[m->currentPlayer].nColor.purple++; break;
        }
    }
    else if (mode == DECREMENT)
    {
        switch(currentCard)
        {
            case 'R': m->activePlayers[m->currentPlayer].nColor.red--; break;
            case 'O': m->activePlayers[m->currentPlayer].nColor.white--; break;
            case 'Y': m->activePlayers[m->currentPlayer].nColor.yellow--; break;
            case 'G': m->activePlayers[m->currentPlayer].nColor.green--; break;
            case 'B': m->activePlayers[m->currentPlayer].nColor.blue--; break;
            case 'I': m->activePlayers[m->currentPlayer].nColor.cyan--; break;
            case 'V': m->activePlayers[m->currentPlayer].nColor.purple--; break;
        }
    }

    
}

void displayTopDeck(Game *m)
{
    printf("\nTop deck: %c%c%c (%d cards remaining in deck)\n", 
        m->drawPile.cards[0].back[0], m->drawPile.cards[0].back[1], m->drawPile.cards[0].back[2], 
        m->drawPile.cardCount);
}

void promptPlayerMove(int currentPlayer, int *option)
{
    printf("\nPlayer %d, what would you like to do?\n", currentPlayer);
    printf("  [1] Try to Score\n");
    printf("  [2] Try to Steal\n");
    askOption(option, 1, 2);
}

void countSameColor(Game *m, Card drawnCard)
{
    int i;
    m->sameColorCount = 0;
    m->sameColorPoints = 0;

    for (i = 0; i < m->activePlayers[m->currentPlayer].tank.cardCount; i++)
    {
        if (m->activePlayers[m->currentPlayer].tank.cards[i].front == drawnCard.front)
        {
            m->sameColorCount++;
            m->sameColorPoints += m->activePlayers[m->currentPlayer].tank.cards[i].points;
            modifyColorCount(m, drawnCard.front, DECREMENT);
        }
    }
    
}

void adjustDeck(Deck deck, int removedCardIndex)
{
    int i;

    for (i = removedCardIndex; i < deck.cardCount; i++)
    {
        deck.cards[i] = deck.cards[i + 1];
    }
    
    deck.cards[i] = emptyCard();
}

int findEmptyCard(Game *m)
{
    int i = 0;
    int emptyCardIndex = NOT_FOUND;
    
    while (emptyCardIndex == NOT_FOUND)
    {
        if (m->activePlayers[m->currentPlayer].tank.cards[i].points == 0)
            emptyCardIndex = i;
        
        i++;
    }

    return emptyCardIndex;
}

#endif // GAME_C;

