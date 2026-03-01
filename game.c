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
    selectPlayers(m);
    setUpGame(m);

    for (int i = 0; i < 15; i++)
        gameLoop(m);
}

/**
 * Loads the settings and cards, shuffles the Draw Pile, and deals out the cards to the players
 * @param m A pointer to the game structure containing the game data
 * @return The function doesn't return anything
 */
void setUpGame(Game *m)
{
    m->gameOver = false;

    loadSettings(m);
    loadCards(m);
    shuffle(m->drawPile.cards, MAX_CARDS, sizeof(Card), m->settings.shuffleSeed);
    initializePlayer(m);
    distributeCards(m);
    displayPlayerState(m);
    displayTopDeck(m);
}

/**
 * Manages the main game loop, iterating through player turns and handling their moves
 * @param m A pointer to the game structure containing the game data
 * @return The function doesn't return anything
 */
void gameLoop(Game *m)
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

        displayPlayerState(m);
        displayTopDeck(m);
    }
}

/**
 * Executes the "Score" action: draws a card and checks if it matches colors in the player's tank
 * @param m A pointer to the game structure containing the game data
 * @return The function doesn't return anything
 */
void tryToScore(Game *m)
{
    Card drawnCard;

    printf("Resolving turn for Player %d...\n", m->currentPlayer + 1);
    drawnCard = drawCard(m);
    printf("- Drawn card color reveal: %c (%d pt/s)!\n", drawnCard.front, drawnCard.points);

    countSameColor(m, drawnCard);
    if (m->sameColorCount > 0)
    {
        printf("- Player %d has (%d) %c card/s worth a total of (%d) pts!\n", m->currentPlayer + 1, m->sameColorCount, drawnCard.front, m->sameColorPoints);
        printf("- +%d points to Player %d's score pile!\n", m->sameColorPoints + drawnCard.points, m->currentPlayer + 1);
        addToScorePile(&m->activePlayers[m->currentPlayer], drawnCard);
        m->activePlayers[m->currentPlayer].currentScore += drawnCard.points + m->sameColorPoints;
    }
    else
    {
        printf("- Player %d has no %c cards...\n", m->currentPlayer + 1, drawnCard.front);
        printf("- Adding drawn card to Player %d's Tank\n", m->currentPlayer + 1);
        addToTank(&m->activePlayers[m->currentPlayer], drawnCard);
    }
}

/**
 * Executes the "Steal" action against another player's tank
 * @param m A pointer to the game structure containing the game data
 * @return The function doesn't return anything
 */
void tryToSteal(Game *m)
{
    // Prompt user who they want to steal from

    // Draw from draw pile

    // If same color found from other player pile
        // Transfer cards with same color to current player's tank
    
    // Else
        // Other player keeps the drawn card
}

void checkWinner(Game *m)
{
    /*
    If the Draw Pile runs out, 
        the player with the most cards in their Score Pile wins. 
        
    If there are players with the same number of cards in their Score Pile, 
        then the player with the most Tank cards wins. 
    
    If those players still have the same number of cards in their Tank, 
        then it is a tie
    */
}

/**  
 * Adds the drawn card to the player's tank
 * @param currentPlayer The player receiving the card
 * @param drawnCard The card that was just drawn from the deck
 */
void addToTank(Player *currentPlayer, Card drawnCard)
{
    int emptyCardIndex = findEmptyCardSlot(currentPlayer->tank);
    currentPlayer->tank.cards[emptyCardIndex] = drawnCard;
    currentPlayer->tank.cardCount++;
    colorCount(currentPlayer, drawnCard.front, INCREMENT);
}

/**  
 * Adds the drawn card and other similar cards in the player's tank to the player's score pile
 * @param currentPlayer The player receiving the card
 * @param drawnCard The card that was just drawn from the deck
 */
void addToScorePile(Player *currentPlayer, Card drawnCard)
{
    int emptyCardIndex;
    int i;

    emptyCardIndex = findEmptyCardSlot(currentPlayer->scorePile);
    currentPlayer->scorePile.cards[emptyCardIndex] = drawnCard;
    for (i = 0; i < currentPlayer->tank.cardCount; i++)
    {
        if (currentPlayer->tank.cards[i].front == drawnCard.front)
        {
            emptyCardIndex = findEmptyCardSlot(currentPlayer->scorePile);
            currentPlayer->scorePile.cards[emptyCardIndex] = currentPlayer->tank.cards[i];
            currentPlayer->scorePile.cardCount++;
            colorCount(currentPlayer, drawnCard.front, DECREMENT);
            adjustDeck(&currentPlayer->tank, i);
            i--;
        }
    }
}

/**
 * Deals the initial set of cards to all active players at the start of the game
 * @param m A pointer to the game structure containing the game data
 * @return The function doesn't return anything
 */
void distributeCards(Game *m)
{
    int i;

    for (m->currentPlayer = 0; m->currentPlayer < m->playerCount; m->currentPlayer++)
    {
        for (i = 0; i < STARTING_CARDS; i++)
        {
            m->activePlayers[m->currentPlayer].tank.cards[i] = drawCard(m);
            m->activePlayers[m->currentPlayer].tank.cardCount++;
            colorCount(&m->activePlayers[m->currentPlayer], m->activePlayers[m->currentPlayer].tank.cards[i].front, INCREMENT);
        }
    }
}

/**
 * Removes and returns the top card from the draw pile, shifting the remaining cards up
 * @param m A pointer to the game structure containing the game data
 * @return The Card structure that was at the top of the deck
 */
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

/**
 * Prints the current state of all players' tanks and their total scores
 * @param m A pointer to the game structure containing the game data
 * @return The function doesn't return anything
 */
void displayPlayerState(Game *m)
{
    int i;

    for (i = 0; i < m->playerCount; i++)
    {
        printf("P%d => [ R: %d | O:%d | Y: %d | G:%d | B:%d | I:%d | V:%d ] // %d\n", i + 1,
            m->activePlayers[i].colorCount.red, m->activePlayers[i].colorCount.white, 
            m->activePlayers[i].colorCount.yellow, m->activePlayers[i].colorCount.green, 
            m->activePlayers[i].colorCount.blue, m->activePlayers[i].colorCount.cyan, 
            m->activePlayers[i].colorCount.purple, m->activePlayers[i].currentScore);
    }
}

/**
 * Resets player statistics, scores, and tanks to their default empty states
 * @param m A pointer to the game structure containing the game data
 * @return The function doesn't return anything
 */
void initializePlayer(Game *m)
{
    int i, j;

    for (i = 0; i < m->playerCount; i++)
    {
        // Empty color count
        m->activePlayers[i].colorCount.white = 0;
        m->activePlayers[i].colorCount.red = 0;
        m->activePlayers[i].colorCount.blue = 0;
        m->activePlayers[i].colorCount.green = 0;
        m->activePlayers[i].colorCount.yellow = 0;
        m->activePlayers[i].colorCount.cyan = 0;
        m->activePlayers[i].colorCount.purple = 0;

        // Empty card count
        m->activePlayers[i].tank.cardCount = 0;

        // Empty current score
        m->activePlayers[i].currentScore = 0;

        // Empty score pile
        m->activePlayers[i].scorePile.cardCount = 0;

        for (j = 0; j < MAX_CARDS; j++)
        {
            // Empty tank
            m->activePlayers[i].tank.cards[j] = emptyCard();

            // Empty score pile
            m->activePlayers[i].scorePile.cards[j] = emptyCard();
        }
    }
}

/**
 * Creates and returns a card with null/zero values to represent an empty slot
 * @return A Card structure initialized to empty values
 */
Card emptyCard()
{
    Card e = {'\0', {'\0', '\0', '\0'}, 0};

    return e;
}

/**
 * Increments or decrements the specific color counter for the current player
 * @param m A pointer to the game structure containing the game data
 * @param currentCard The color character to be modified
 * @param mode The operation mode (INCREMENT or DECREMENT)
 * @return The function doesn't return anything
 */
void colorCount(Player *currentPlayer, Color currentCard, char mode)
{
    if (mode == INCREMENT)
    {
        switch(currentCard)
        {
            case 'R': currentPlayer->colorCount.red++; break;
            case 'O': currentPlayer->colorCount.white++; break;
            case 'Y': currentPlayer->colorCount.yellow++; break;
            case 'G': currentPlayer->colorCount.green++; break;
            case 'B': currentPlayer->colorCount.blue++; break;
            case 'I': currentPlayer->colorCount.cyan++; break;
            case 'V': currentPlayer->colorCount.purple++; break;
        }
    }
    else if (mode == DECREMENT)
    {
        switch(currentCard)
        {
            case 'R': currentPlayer->colorCount.red--; break;
            case 'O': currentPlayer->colorCount.white--; break;
            case 'Y': currentPlayer->colorCount.yellow--; break;
            case 'G': currentPlayer->colorCount.green--; break;
            case 'B': currentPlayer->colorCount.blue--; break;
            case 'I': currentPlayer->colorCount.cyan--; break;
            case 'V': currentPlayer->colorCount.purple--; break;
        }
    }
}

/**
 * Displays the back-side of the top card in the draw pile and the total deck count
 * @param m A pointer to the game structure containing the game data
 * @return The function doesn't return anything
 */
void displayTopDeck(Game *m)
{
    printf("\nTop deck: %c%c%c (%d cards remaining in deck)\n", 
        m->drawPile.cards[0].back[0], m->drawPile.cards[0].back[1], m->drawPile.cards[0].back[2], 
        m->drawPile.cardCount);
}

/**
 * Prompts the user to choose between scoring or stealing during their turn
 * @param currentPlayer The index/number of the player currently acting
 * @param option A pointer to the integer where the player's choice will be stored
 * @return The function doesn't return anything
 */
void promptPlayerMove(int currentPlayer, int *option)
{
    printf("\nPlayer %d, what would you like to do?\n", currentPlayer);
    printf("  [1] Try to Score\n");
    printf("  [2] Try to Steal\n");
    askOption(option, 1, 2);
}

/**
 * Checks the current player's tank for cards matching the drawn card's color and calculates points
 * @param m A pointer to the game structure containing the game data
 * @param drawnCard The card that was just drawn from the deck
 * @return The function doesn't return anything
 */
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
        }
    }
}

/**
 * Shifts cards in a deck to fill a gap left by a removed card
 * @param deck The deck structure to be modified
 * @param removedCardIndex The index of the card that was removed
 * @return The function doesn't return anything
 */
void adjustDeck(Deck *deck, int removedCardIndex)
{
    int i;

    for (i = removedCardIndex; i < deck->cardCount; i++)
    {
        deck->cards[i] = deck->cards[i + 1];
    }
    
    deck->cards[i] = emptyCard();
    deck->cardCount--;
}

/**
 * Searches the current player's tank for the first available empty card slot
 * @param m A pointer to the game structure containing the game data
 * @return The index of the first empty card slot found
 */
int findEmptyCardSlot(Deck cards)
{
    return cards.cardCount;
}

#endif // GAME_C