/**
 * Description : Contains the functions that handles the gameplay of Mantis
 * Author/s : De Dios, Justin Marco C.
 *            Ocampo, Kysha Denise D.
 *  Section : S12A & S22A
 *  Last Modified : 03-25-2026
 */

#ifndef GAME_C 
#define GAME_C 

#include <stdio.h>
#include <string.h>

#include "defs.h"

/**
 * Starts a new game of Mantis from player selection, game flow, and updates the player stats based on the game result
 * @param m A pointer to the game structure containing the game data
 */
void newGame(Game *m)
{
    selectPlayers(m);
    iClear(0, 0, CONSOLE_WIDTH, CONSOLE_HEIGHT);
    setUpGame(m);
    gameLoop(m);
    displayWinner(m);
    updatePlayerData(m);
}

/**
 * Loads the settings and cards, shuffles the Draw Pile, and deals out the cards to the players
 * @param m A pointer to the game structure containing the game data
 */
void setUpGame(Game *m)
{
    loadSettings(m);
    loadCards(m);
    shuffle(m->drawPile.cards, MAX_CARDS, sizeof(Card), m->settings.shuffleSeed);
    distributeCards(m);
}

/**
 * Manages the main game loop, iterating through player turns and handling their moves
 * @param m A pointer to the game structure containing the game data
 */
void gameLoop(Game *m)
{
    int option;

    do
    {
        for (m->currentPlayer = 0; m->currentPlayer < m->playerCount; m->currentPlayer++)
        {
            displayPlayerState(m, INACTIVE);
            displayTopDeck(m);
            displayPlayerState(m, ACTIVE);

            promptPlayerMove(m, &option);

            switch(option)
            {
                case 1: tryToScore(m); break;
                case 2: tryToSteal(m); break;
            }
            waitEnter();
            iClear(0, 0, CONSOLE_WIDTH, CONSOLE_HEIGHT);

            checkWinner(m);
        }
    } while (!m->gameOver && m->drawPile.cardCount > 0);

    if (m->drawPile.cardCount == 0 && !m->foundWinner)
    {
        checkSpecialWinner(m);
    }
}

/**
 * Checks if a player has won the game if they have matched or exceeded the winning points
 * @param m A pointer to the game structure containing the game data
 */
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

/**
 * Checks the special win condition when the draw pile runs out
 * @param m A pointer to the game structure containing the game data
 */
void checkSpecialWinner(Game *m)
{ 
    int tiedIndices[MAX_PLAYERS];
    int tiedCount = 0;
    int mostScore = -1;
    int mostTanks = -1;

    for (int i = 0; i < m->playerCount; i++)
        if (m->activePlayers[i].scorePile.totalScore > mostScore)
            mostScore = m->activePlayers[i].scorePile.totalScore;

    for (int i = 0; i < m->playerCount; i++)
        if (m->activePlayers[i].scorePile.totalScore == mostScore)
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
        for (int i = 0; i < tiedCount; i++)
            if (m->activePlayers[tiedIndices[i]].tank.cardCount > mostTanks)
                mostTanks = m->activePlayers[tiedIndices[i]].tank.cardCount;

        tiedCount = 0;
        for (int i = 0; i < m->playerCount; i++)
            if (m->activePlayers[i].tank.cardCount == mostTanks)
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
 * Deals the initial set of cards to all active players at the start of the game
 * @param m A pointer to the game structure containing the game data
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
 */
void displayPlayerState(Game *m, int playerType)
{
    int i;

    if (playerType == INACTIVE)
    {
        for (i = 0; i < m->playerCount; i++)
        {
            if (i != m->currentPlayer)
            {
                printf("[%s]\n", m->activePlayers[i].username);
                displayFrontSideDeck(m->activePlayers[i].tank, SMALL);
                printf("\n");
                printf("[Score: %d]\n\n", m->activePlayers[i].scorePile.totalScore);
            }
        }
    }
    else if (playerType == ACTIVE)
    {
        printf("\n[%s]\n", m->activePlayers[m->currentPlayer].username);
        displayFrontSideDeck(m->activePlayers[m->currentPlayer].tank, BIG);
        printf("[Score]: %d\n", m->activePlayers[m->currentPlayer].scorePile.totalScore);
    }
}

/**
 * Displays the back-side of the top card in the draw pile and the total deck count
 * @param m A pointer to the game structure containing the game data
 */
void displayTopDeck(Game *m)
{
    printf("[TOP DECK]\n");
    displayCard(m->drawPile.cards[0], BIG, BACK);
    printf("(%d left)\n", m->drawPile.cardCount);
}

/**
 * Prompts the user to choose between scoring or stealing during their turn
 * @param currentPlayer The index of the currnet player making the move
 * @param option A pointer to the user's chosen option
 */
void promptPlayerMove(Game *m, int *option)
{
    printf("\n%s, what would you like to do?\n", m->activePlayers[m->currentPlayer].username);
    printf("  [1] Try to Score\n");
    printf("  [2] Try to Steal\n");
    askOption(option, 1, 2);
}

/**
 * Executes the "Score" action: draws a card and checks if it matches colors in the player's tank
 * @param m A pointer to the game structure containing the game data
 */
void tryToScore(Game *m)
{
    m->drawnCard = drawCard(m);
    revealCard(m->drawnCard);

    checkSameColor(m, m->activePlayers[m->currentPlayer].tank);
    if (m->sameColorCount > 0)
    {
        pauseScreen(2.0);
        printf("%s has (%d) ", m->activePlayers[m->currentPlayer].username, m->sameColorCount);
        setColor(m->drawnCard.front);
        printf("%c ", m->drawnCard.front);
        setColor(WHITE);
        printf("card/s worth a total of (%d) pts!\n", m->sameColorPoints);
        pauseScreen(2.0);
        printf("+%d points to %s's score pile!\n", m->sameColorPoints + m->drawnCard.points, m->activePlayers[m->currentPlayer].username);
        addToScorePile(&m->activePlayers[m->currentPlayer], m->drawnCard);
    }
    else
    {
        pauseScreen(2.0);
        printf("%s has no ", m->activePlayers[m->currentPlayer].username);
        setColor(m->drawnCard.front);
        printf("%c ", m->drawnCard.front);
        setColor(WHITE);
        printf("cards...\n");
        pauseScreen(2.0);
        printf("Adding drawn card to %s's Tank\n", m->activePlayers[m->currentPlayer].username);
        addToTank(&m->activePlayers[m->currentPlayer], m->drawnCard);
    }
}

/**
 * Executes the "Steal" action: draws a card and checks if it matches colors in the other player's tank
 * @param m A pointer to the game structure containing the game data
 */
void tryToSteal(Game *m)
{
    promptSteal(m);
    m->drawnCard = drawCard(m);
    revealCard(m->drawnCard);

    checkSameColor(m, m->activePlayers[m->stolenPlayer].tank);

    if (m->sameColorCount > 0)
    {
        pauseScreen(2.0);
        printf("%s has (%d) ", m->activePlayers[m->stolenPlayer].username, m->sameColorCount);
        setColor(m->drawnCard.front);
        printf("%c", m->drawnCard.front);
        setColor(WHITE);
        printf(" cards/s!\n");
        pauseScreen(2.0);
        printf("+%d (", 1 + m->sameColorCount);
        setColor(m->drawnCard.front);
        printf("%c", m->drawnCard.front);
        setColor(WHITE);
        printf(") cards to %s's Tank!\n", m->activePlayers[m->currentPlayer].username);
        addToTank(&m->activePlayers[m->currentPlayer], m->drawnCard);
        stealTank(&m->activePlayers[m->currentPlayer], &m->activePlayers[m->stolenPlayer], m->drawnCard.front);
    }
    else
    {
        pauseScreen(2.0);
        printf("%s has no ", m->activePlayers[m->stolenPlayer].username);
        setColor(m->drawnCard.front);
        printf("%c ", m->drawnCard.front);
        setColor(WHITE);
        printf("cards...\n");
        pauseScreen(2.0);
        printf("Adding drawn card to %s's Tank\n", m->activePlayers[m->stolenPlayer].username);
        addToTank(&m->activePlayers[m->stolenPlayer], m->drawnCard);
    }
}

/**
 * Steals the cards from the stolen player's tank to the current player's tank
 * @param currentPlayer A pointer to the current player's structure containing the player data
 * @param currentPlayer A pointer to the stolen player's structure containing the player data
 * @param drawnCard The color of the drawn card
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
 * @param option A pointer to the user's chosen option
 */
void promptSteal(Game *m)
{
    printf("\nWho would you like to steal from?\n");
    for (int i = 0; i < m->playerCount - 1; i++)
    {
        printf("  [%d] ", i + 1);
        if (i >= m->currentPlayer)
            printf("%s", m->activePlayers[i + 1].username);
        else
            printf("%s", m->activePlayers[i].username);
        printf("\n");
    }
    askOption(&m->stolenPlayer, 1, m->playerCount - 1);

    if (m->stolenPlayer <= m->currentPlayer)
        m->stolenPlayer -= 1;
}

/**
 * Removes and returns the top card from the draw pile, shifting the remaining cards up
 * @param m A pointer to the game structure containing the game data
 * @return The Card that was at the top of the deck
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
 * @param m A pointer to the game structure containing the game data
 * @param tank Cards in the player's tank
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
 * @param currentPlayer A pointer to the current player's structure containing the player data
 * @param drawnCard The card drawn from the draw pile
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
 * @param currentPlayer A pointer to the current player's structure containing the player data
 * @param drawnCard The card drawn from the draw pile
 */
void addToTank(Player *currentPlayer, Card drawnCard)
{
    currentPlayer->tank.cards[emptyCardIndex(currentPlayer->tank)] = drawnCard;
    currentPlayer->tank.cardCount++;
    colorCount(&currentPlayer->tank, drawnCard.front, INCREMENT);
}

/**  
 * Calculates the total score in the score pile
 * @param currentPlayer A pointer to the current player's structure containing the player data
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
 * @param currentDeck A pointer to the current deck's structure containing the deck data
 * @param currentCard The color of the current card
 * @param mode The operation mode (INCREMENT or DECREMENT)
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

/**
 * Displays the winner/s of mantis
 * @param currentDeck The deck being checked
 */
void displayWinner(Game *g)
{
    printf("Winner/s:\n");
    for (int i = 0; i < g->winnerCount; i++)
    {
        printf("%s\n", g->activePlayers[g->winner[i]].username);
    }
}

/**
 * Updates "player.txt" with the updated player stats
 * @param currentDeck The deck being checked
 */
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

/**
 * Prints the an emoticon of it's respective color
 * @param currentColor The color of the current card
 * @return void
 */
void printEmoticon(Color currentColor)
{
    setColor(currentColor);
    switch (currentColor)
    {
        case WHITE: printf(":/"); break;
        case RED: printf(":O"); break;
        case BLUE: printf(":("); break;
        case GREEN: printf("XD"); break;
        case YELLOW: printf("B)"); break;
        case CYAN: printf(":>"); break;
        case PURPLE: printf(":3"); break;
    }
}

/**
 * Displays the card depending on the user's desired size or desired side
 * @param currentCard The card being displayed
 * @param cardSize The desired card size to be displayed (BIG or SMALL)
 * @param cardSide The desired card side to be displayed (FRONT or BACK)
 * @return void
 */
void displayCard(Card currentCard, int cardSize, int cardSide)
{
    if (cardSize == SMALL)
    {
        setColor(currentCard.front);
        printf("[ ");
        printEmoticon(currentCard.front);
        printf(" ] ");
    }
    else if (cardSize == BIG)
    {
        if (cardSide == FRONT)
        {
            setColor(currentCard.front);
            printf("+------+\n");
            printf("|      |\n");
            printf("|  ");
            printEmoticon(currentCard.front);
            printf("  |\n");
            printf("|      |\n");
            printf("+------+\n");
        }
        else if (cardSide == BACK)
        {
            printf("+------+\n");
            printf("| ");
            printEmoticon(currentCard.back[0]);
            setColor(WHITE);
            printf("   |\n");
            printf("|  ");
            printEmoticon(currentCard.back[1]);
            setColor(WHITE);
            printf("  |\n");
            printf("|   ");
            printEmoticon(currentCard.back[2]);
            setColor(WHITE);
            printf(" |\n");
            printf("+------+\n");
        }
    }
    setColor(WHITE);
}

/**
 * Displays card deck's front side
 * @param currentDeck The deck being displayed
 * @param cardSize The desired card size to be displayed (BIG or SMALL)
 * @return void
 */
void displayFrontSideDeck(Deck currentDeck, int cardSize)
{
    int i;

    if (cardSize == SMALL)
    {
        for (i = 0; i < currentDeck.cardCount; i++)
        {
            displayCard(currentDeck.cards[i], SMALL, FRONT);
        }
    }
    else if (cardSize == BIG)
    {
        for (i = 0; i < currentDeck.cardCount; i++)
        {
            setColor(currentDeck.cards[i].front);
            printf("+------+ ");
        }
        printf("\n");
        for (i = 0; i < currentDeck.cardCount; i++)
        {
            setColor(currentDeck.cards[i].front);
            printf("|      | ");
        }
        printf("\n");
        for (i = 0; i < currentDeck.cardCount; i++)
        {
            setColor(currentDeck.cards[i].front);
            printf("|  ");
            printEmoticon(currentDeck.cards[i].front);
            printf("  | ");
        }
        printf("\n");
        for (i = 0; i < currentDeck.cardCount; i++)
        {
            setColor(currentDeck.cards[i].front);
            printf("|      | ");
        }
        printf("\n");
        for (i = 0; i < currentDeck.cardCount; i++)
        {
            setColor(currentDeck.cards[i].front);
            printf("+------+ ");
        }
        printf("\n");
    }
    setColor(WHITE);
}

/**
 * Reveals the front side of the drawn card
 * @param drawnCard The card drawn from the draw pile
 * @return void
 */
void revealCard(Card drawnCard)
{
    int i;
    
    printf("Revealing card");
    for (i = 0; i < 3; i++)
    {
        pauseScreen(1.0);
        printf(".");
    }
    printf("\n");
    displayCard(drawnCard, BIG, FRONT);
    printf("Drawn card worth (%d pt/s)!\n", drawnCard.points);
}

#endif // GAME_C