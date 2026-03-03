#ifndef GAME_C 
#define GAME_C 

#include <stdio.h>
#include <string.h>

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
    gameLoop(m);
    displayWinner(m);
    updatePlayerData(m);
}

/**
 * Loads the settings and cards, shuffles the Draw Pile, and deals out the cards to the players
 * @param m A pointer to the game structure containing the game data
 * @return The function doesn't return anything
 */
void setUpGame(Game *m)
{
    loadSettings(m);
    loadCards(m);
    shuffle(m->drawPile.cards, MAX_CARDS, sizeof(Card), m->settings.shuffleSeed);
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

    do
    {
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
            checkWinner(m);
        }
    } while (!m->gameOver && m->drawPile.cardCount > 0);

    if (m->drawPile.cardCount == 0 && !m->foundWinner)
    {
        checkSpecialWinner(m);
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
            colorCount(&m->activePlayers[m->currentPlayer].tank, m->activePlayers[m->currentPlayer].tank.cards[i].front, INCREMENT);
        }
    }
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
            m->activePlayers[i].tank.colorCount.red, m->activePlayers[i].tank.colorCount.white, 
            m->activePlayers[i].tank.colorCount.yellow, m->activePlayers[i].tank.colorCount.green, 
            m->activePlayers[i].tank.colorCount.blue, m->activePlayers[i].tank.colorCount.cyan, 
            m->activePlayers[i].tank.colorCount.purple, m->activePlayers[i].scorePile.totalScore);
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

void checkWinner(Game *m)
{
    if (m->activePlayers[m->currentPlayer].scorePile.totalScore >= m->settings.winningPoints)
    {
        m->winner[0] = m->currentPlayer;
        m->winnerCount++;
        m->foundWinner = true;
        m->gameOver = true;
    }
}

void checkSpecialWinner(Game *m)
{ 
    int tiedIndices[MAX_PLAYERS];
    int tiedCount = 0;
    int mostCards = -1;

    for (int i = 0; i < m->playerCount; i++)
        if (m->activePlayers[i].scorePile.cardCount > mostCards)
            mostCards = m->activePlayers[i].scorePile.cardCount;

    for (int i = 0; i < m->playerCount; i++)
        if (m->activePlayers[i].scorePile.cardCount == mostCards)
        {
            tiedIndices[tiedCount] = i;
            tiedCount++;
        }
            
    if (tiedCount == 1)
    {
        m->winner[0] = tiedIndices[0];
        m->winnerCount = 1;
        m->foundWinner = true;
    }

    if (!m->foundWinner)
    {
        mostCards = -1;
        for (int i = 0; i < tiedCount; i++)
            if (m->activePlayers[tiedIndices[i]].tank.cardCount > mostCards)
                mostCards = m->activePlayers[tiedIndices[i]].tank.cardCount;

        tiedCount = 0;
        for (int i = 0; i < m->playerCount; i++)
            if (m->activePlayers[i].tank.cardCount == mostCards)
            {
                tiedIndices[tiedCount] = i;
                tiedCount++;
            }

        if (tiedCount == 1)
        {
            m->winner[0] = tiedIndices[0];
            m->winnerCount = 1;
            m->foundWinner = true;
        }
        else
        {
            for (int i = 0; i < tiedCount; i++)
            {
                m->winner[i] = tiedIndices[i];
                m->winnerCount++;
            }
            m->tieGame = true;
        }
    }
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
 * Executes the "Score" action: draws a card and checks if it matches colors in the player's tank
 * @param m A pointer to the game structure containing the game data
 * @return The function doesn't return anything
 */
void tryToScore(Game *m)
{
    printf("Resolving turn for Player %d...\n", m->currentPlayer + 1);

    m->drawnCard = drawCard(m);
    printf("- Drawn card color reveal: %c (%d pt/s)!\n", m->drawnCard.front, m->drawnCard.points);

    checkSameColor(m, m->activePlayers[m->currentPlayer].tank);

    if (m->sameColorCount > 0)
    {
        printf("- Player %d has (%d) %c card/s worth a total of (%d) pts!\n", 
            m->currentPlayer + 1, m->sameColorCount, m->drawnCard.front, m->sameColorPoints);
        printf("- +%d points to Player %d's score pile!\n", m->sameColorPoints + m->drawnCard.points, m->currentPlayer + 1);
        addToScorePile(&m->activePlayers[m->currentPlayer], m->drawnCard);
    }
    else
    {
        printf("- Player %d has no %c cards...\n", m->currentPlayer + 1, m->drawnCard.front);
        printf("- Adding drawn card to Player %d's Tank\n", m->currentPlayer + 1);
        addToTank(&m->activePlayers[m->currentPlayer], m->drawnCard);
    }
}

/**
 * Executes the "Steal" action: draws a card and checks if it matches colors in the other player's tank
 * @param m A pointer to the game structure containing the game data
 * @return The function doesn't return anything
 */
void tryToSteal(Game *m)
{
    int chosenPlayer;

    promptSteal(m, &chosenPlayer);
    
    printf("Resolving turn for Player %d...\n", m->currentPlayer + 1);

    m->drawnCard = drawCard(m);
    printf("- Drawn card color reveal: %c (%d pt/s)!\n", m->drawnCard.front, m->drawnCard.points);

    checkSameColor(m, m->activePlayers[chosenPlayer].tank);

    if (m->sameColorCount > 0)
    {
        printf("- Player %d has (%d) %c card/s!\n", chosenPlayer + 1, m->sameColorCount, m->drawnCard.front);
        printf("- +%d (%c) cards to Player %d's Tank!\n", 1 + m->sameColorCount, m->drawnCard.front, m->currentPlayer + 1);
        addToTank(&m->activePlayers[m->currentPlayer], m->drawnCard);
        stealTank(&m->activePlayers[m->currentPlayer], &m->activePlayers[chosenPlayer], m->drawnCard.front);
    }
    else
    {
        printf("- Player %d has no %c cards...\n", chosenPlayer + 1, m->drawnCard.front);
        printf("- Adding drawn card to Player %d's Tank\n", chosenPlayer + 1);
        addToTank(&m->activePlayers[chosenPlayer], m->drawnCard);
    }
}

/**
 * Steals the cards from the stolen player's tank to the current player's tank
 * @param currentPlayer A pointer to the player performing the steal
 * @param stolenPlayer A pointer to player being stolen
 * @param drawnCard The color of the drawn card
 * @return The function doesn't return anything
 */
void stealTank(Player *currentPlayer, Player *stolenPlayer, Color drawnCard)
{
    // Add cards from tank with same color to score pile
    for (int i = 0; i < stolenPlayer->tank.cardCount; i++)
    {
        if (stolenPlayer->tank.cards[i].front == drawnCard)
        {
            // Add same color cards from stolen player's tank to current player's tank
            currentPlayer->tank.cards[emptyCardIndex(currentPlayer->tank)] = stolenPlayer->tank.cards[i];
            currentPlayer->tank.cardCount++;
            colorCount(&currentPlayer->tank, drawnCard, INCREMENT);

            // Remove same color cards in tank of stolen player
            adjustDeck(&stolenPlayer->tank, i);
            stolenPlayer->tank.cardCount--;
            colorCount(&stolenPlayer->tank, drawnCard, DECREMENT);

            i--;
        }
    }
}

/**
 * Prompts the current player on which player they want to steal from
 * @param m A pointer to the game structure containing the game data
 * @param option A pointer where the player's option will be stored
 * @return The function doesn't return anything
 */
void promptSteal(Game *m, int *option)
{
    printf("Who would you like to steal from?\n");
    for (int i = 0; i < m->playerCount - 1; i++)
    {
        printf("  [%d] Player ", i + 1);
        if (i >= m->currentPlayer)
            printf("%d", i + 2);
        else
            printf("%d", i + 1);
        printf("\n");
    }
    askOption(option, 1, m->playerCount - 1);

    if (*option <= m->currentPlayer)
        *option -= 1;
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
 * Checks the tank if there are cards with the same color as drawn card 
 * @param m A pointer to the game structure containing the game data; 
 *          updates m->sameColorCount and m->sameColorPoints based on matches found in the tank
 * @return The function doesn't return anything
 */
void checkSameColor(Game *m, Deck tank)
{
    m->sameColorCount = 0;
    m->sameColorPoints = 0;

    for (int i = 0; i < tank.cardCount; i++)
    {
        if (tank.cards[i].front == m->drawnCard.front)
        {
            m->sameColorCount++;
            m->sameColorPoints += tank.cards[i].points;
        }
    }
}

/**  
 * Adds the drawn card and similar cards in the player's tank to the player's score pile
 * @param currentPlayer A pointer to the player receiving the card; 
 *                      updating the current player's tank or score pile
 * @param drawnCard The card that was drawn from the deck
 */
void addToScorePile(Player *currentPlayer, Card drawnCard)
{
    // Add drawn card to score pile
    currentPlayer->scorePile.cards[emptyCardIndex(currentPlayer->scorePile)] = drawnCard;
    currentPlayer->scorePile.cardCount++;

    // Add cards from tank with same color to score pile
    for (int i = 0; i < currentPlayer->tank.cardCount; i++)
    {
        if (currentPlayer->tank.cards[i].front == drawnCard.front)
        {
            // Add same color cards in score pile
            currentPlayer->scorePile.cards[emptyCardIndex(currentPlayer->scorePile)] = currentPlayer->tank.cards[i];
            currentPlayer->scorePile.cardCount++;
            colorCount(&currentPlayer->scorePile, drawnCard.front, INCREMENT);

            // Remove same color cards in tank
            adjustDeck(&currentPlayer->tank, i);
            currentPlayer->tank.cardCount--;
            colorCount(&currentPlayer->tank, drawnCard.front, DECREMENT);

            i--;
        }
    }

    calculateScore(currentPlayer);
}

/**  
 * Adds the drawn card to the player's tank
 * @param currentPlayer A pointer to the player receiving the card;
 *                      updating the deck structure, card count, and color count
 * @param drawnCard The card that was just drawn from the deck
 */
void addToTank(Player *currentPlayer, Card drawnCard)
{
    currentPlayer->tank.cards[emptyCardIndex(currentPlayer->tank)] = drawnCard;
    currentPlayer->tank.cardCount++;
    colorCount(&currentPlayer->tank, drawnCard.front, INCREMENT);
}

/**  
 * Calculates the total score in the score pile
 * @param currentPlayer A pointer to the player receiving the card; 
 *                      updates the total score in the player's score pile
 * @return The function doesn't return anything
 */
void calculateScore(Player *currentPlayer)
{
    currentPlayer->scorePile.totalScore = 0;

    for (int i = 0; i < currentPlayer->scorePile.cardCount; i++)
    {
        currentPlayer->scorePile.totalScore += currentPlayer->scorePile.cards[i].points;
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
}

/**
 * Increments or decrements the color count of the deck
 * @param currentDeck A pointer to the deck structure where the color count is stored;
 *                    currentDeck->colorCount is either incremented or decremented
 * @param currentCard The color of the current card
 * @param mode The operation mode (INCREMENT or DECREMENT)
 * @return The function doesn't return anything
 */
void colorCount(Deck *currentDeck, Color currentCard, char mode)
{
    if (mode == INCREMENT)
    {
        switch(currentCard)
        {
            case 'R': currentDeck->colorCount.red++; break;
            case 'O': currentDeck->colorCount.white++; break;
            case 'Y': currentDeck->colorCount.yellow++; break;
            case 'G': currentDeck->colorCount.green++; break;
            case 'B': currentDeck->colorCount.blue++; break;
            case 'I': currentDeck->colorCount.cyan++; break;
            case 'V': currentDeck->colorCount.purple++; break;
        }
    }
    else if (mode == DECREMENT)
    {
        switch(currentCard)
        {
            case 'R': currentDeck->colorCount.red--; break;
            case 'O': currentDeck->colorCount.white--; break;
            case 'Y': currentDeck->colorCount.yellow--; break;
            case 'G': currentDeck->colorCount.green--; break;
            case 'B': currentDeck->colorCount.blue--; break;
            case 'I': currentDeck->colorCount.cyan--; break;
            case 'V': currentDeck->colorCount.purple--; break;
        }
    }
}

/**
 * Returns the index where the next card should be inserted
 * @param currentDeck The deck being checked
 * @return The index of the first empty card slot
 */
int emptyCardIndex(Deck currentDeck)
{
    return currentDeck.cardCount;
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

void displayWinner(Game *g)
{
    printf("Winner/s:\n");
    for (int i = 0; i < g->winnerCount; i++)
    {
        printf("%s\n", g->activePlayers[g->winner[i]].username);
    }
}

void updatePlayerData(Game *g)
{
    FILE *playerFile;

    for (int i = 0; i < g->playerCount; i++)
    {
        g->activePlayers[i].totalScore += g->activePlayers[i].scorePile.totalScore;
    }

    playerFile = fopen("players.txt", "w");

    // Write data of players who just played
    for (int i = 0; i < g->playerCount; i++)
    {
        fprintf(playerFile ,"%s,%d,%d\n", g->activePlayers[i].username, g->activePlayers[i].wins, g->activePlayers[i].totalScore);
    }

    // Write data of players who didn't play
    for (int i = 0; i < g->totalPlayers - g->playerCount; i++)
    {
        fprintf(playerFile ,"%s,%d,%d\n", g->playerData[i].username, g->playerData[i].wins, g->playerData[i].totalScore);
    }

    fclose(playerFile);
}

#endif // GAME_C