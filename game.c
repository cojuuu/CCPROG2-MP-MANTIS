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
 * @return void
 */
void newGame(Game *m)
{
    selectPlayers(m);
    setUpGame(m);
    gameLoop(m);
    displayWinner(m);
    updatePlayerData(m);
    goBackToMainMenu(m);
}

/**
 * Loads the settings and cards, shuffles the Draw Pile, and deals out the cards to the players
 * @param m A pointer to the game structure containing the game data
 * @return void
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
    distributeCards(m);
}

/**
 * Deals the initial set of cards to all active players at the start of the game
 * @param m A pointer to the game structure containing the game data
 * @return void
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
 * Manages the main game loop, iterating through player turns and handling their moves
 * @param m A pointer to the game structure containing the game data
 * @return void
 */
void gameLoop(Game *m)
{
    do
    {
        for (m->currentPlayer = 0; m->currentPlayer < m->playerCount; m->currentPlayer++)
        {
            displayPlayerState(m, INACTIVE);
            displayTopDeck(m);
            displayPlayerState(m, ACTIVE);

            promptPlayerMove(m);

            switch(m->nav.selectedOption)
            {
                case 0: tryToScore(m); break;
                case 1: tryToSteal(m); break;
            }
            waitEnter("Press enter to continue...");
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
 * @return void
 */
void checkWinner(Game *m)
{
    if (m->activePlayers[m->currentPlayer].scorePile.totalScore >= m->settings.winningPoints)
    {
        m->winner[0] = m->currentPlayer;
        m->winnerCount++;
        m->foundWinner = true;
        m->gameOver = true;
        m->currentPlayer = m->playerCount;
    }
}

/**
 * Checks the special win condition when the draw pile runs out
 * @param m A pointer to the game structure containing the game data
 * @return void
 */
void checkSpecialWinner(Game *m)
{ 
    int i;
    int tiedIndices[MAX_PLAYERS];
    int tiedCount = 0;
    int mostScore = -1;
    int mostTanks = -1;

    for (i = 0; i < m->playerCount; i++)
        if (m->activePlayers[i].scorePile.totalScore > mostScore)
            mostScore = m->activePlayers[i].scorePile.totalScore;

    for (i = 0; i < m->playerCount; i++)
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
        for (i = 0; i < tiedCount; i++)
            if (m->activePlayers[tiedIndices[i]].tank.cardCount > mostTanks)
                mostTanks = m->activePlayers[tiedIndices[i]].tank.cardCount;

        tiedCount = 0;
        for (i = 0; i < m->playerCount; i++)
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
            for (i = 0; i < tiedCount; i++)
            {
                m->winner[i] = tiedIndices[i];
                m->winnerCount++;
            }
            m->tieGame = true;
        }
    }
}

/** 
 * Resets the in game data and returns to the main menu
 * @param m A pointer to the game structure containing the game data
 * @return void
 */
void goBackToMainMenu(Game *m)
{
    setColor(MAGENTA);
    waitEnter("    Press enter to go back to the main menu...");
    setColor(WHITE);
    iClear(0, 0, CONSOLE_WIDTH, CONSOLE_HEIGHT);
    memset(m, 0, sizeof(*m));
    mainMenu(m);
}

/**
 * Prompts the user to choose between scoring or stealing during their turn
 * @param m A pointer to the game structure containing the game data
 * @return void
 */
void promptPlayerMove(Game *m)
{
    String36 playerMoves[] = {"S C O R E", "S T E A L"};

    printf("\n%s, what would you like to do?\n", m->activePlayers[m->currentPlayer].username);
    interactiveMenu1D(&m->nav, playerMoves, 2);
}

/**
 * Prompts the current player on which player they want to steal from
 * @param m A pointer to the game structure containing the game data
 * @return void
 */
void promptSteal(Game *m)
{
    String36 stealOptions[MAX_PLAYERS];
    int optionsAdded = 0;
    int i;

    for (i = 0; i < m->playerCount; i++)
    {
        if (i != m->currentPlayer)
        {
            strcpy(stealOptions[optionsAdded], m->activePlayers[i].username);
            optionsAdded++;
        }
    }

    getCursorPosition(&m->nav.x, &m->nav.y);
    iClear(m->nav.x, m->nav.y - 1, 50, 5);
    printf("%s, who would you like to steal from?\n", m->activePlayers[m->currentPlayer].username);
    interactiveMenu1D(&m->nav, stealOptions, m->playerCount - 1);
    m->stolenPlayer = m->nav.selectedOption;

    if (m->stolenPlayer >= m->currentPlayer)
        m->stolenPlayer++;
}

/**
 * Removes and returns the top card from the draw pile, shifting the remaining cards up
 * @param m A pointer to the game structure containing the game data
 * @return The drawn card that was at the top of the deck
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
 * Executes the "Score" action: draws a card and checks if it matches colors in the player's tank
 * @param m A pointer to the game structure containing the game data
 * @return void
 */
void tryToScore(Game *m)
{
    m->drawnCard = drawCard(m);
    revealCard(m->drawnCard);

    checkSameColor(m, m->activePlayers[m->currentPlayer].tank);
    if (m->sameColorCount > 0)
    {
        // pauseScreen(2.0);
        printf("%s has (%d) ", m->activePlayers[m->currentPlayer].username, m->sameColorCount);
        setColor(m->drawnCard.front);
        printf("%c ", m->drawnCard.front);
        setColor(WHITE);
        printf("card/s worth a total of (%d) pts!\n", m->sameColorPoints);
        // pauseScreen(2.0);
        printf("+%d points to %s's score pile!\n", m->sameColorPoints + m->drawnCard.points, m->activePlayers[m->currentPlayer].username);
        addToScorePile(&m->activePlayers[m->currentPlayer], m->drawnCard);
    }
    else
    {
        // pauseScreen(2.0);
        printf("%s has no ", m->activePlayers[m->currentPlayer].username);
        setColor(m->drawnCard.front);
        printf("%c ", m->drawnCard.front);
        setColor(WHITE);
        printf("cards...\n");
        // pauseScreen(2.0);
        printf("Adding drawn card to %s's Tank\n", m->activePlayers[m->currentPlayer].username);
        addToTank(&m->activePlayers[m->currentPlayer], m->drawnCard);
    }
}

/**
 * Executes the "Steal" action: draws a card and checks if it matches colors in the other player's tank
 * @param m A pointer to the game structure containing the game data
 * @return void
 */
void tryToSteal(Game *m)
{
    promptSteal(m);
    m->drawnCard = drawCard(m);
    revealCard(m->drawnCard);

    checkSameColor(m, m->activePlayers[m->stolenPlayer].tank);

    if (m->sameColorCount > 0)
    {
        // pauseScreen(2.0);
        printf("%s has (%d) ", m->activePlayers[m->stolenPlayer].username, m->sameColorCount);
        setColor(m->drawnCard.front);
        printf("%c", m->drawnCard.front);
        setColor(WHITE);
        printf(" cards/s!\n");
        // pauseScreen(2.0);
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
        // pauseScreen(2.0);
        printf("%s has no ", m->activePlayers[m->stolenPlayer].username);
        setColor(m->drawnCard.front);
        printf("%c ", m->drawnCard.front);
        setColor(WHITE);
        printf("cards...\n");
        // pauseScreen(2.0);
        printf("Adding drawn card to %s's Tank\n", m->activePlayers[m->stolenPlayer].username);
        addToTank(&m->activePlayers[m->stolenPlayer], m->drawnCard);
    }
}

/**  
 * Adds the drawn card and similar cards in the player's tank to the player's score pile
 * @param currentPlayer A pointer to the current player's structure containing the player data
 * @param drawnCard The card drawn from the draw pile
 * @return void
 */
void addToScorePile(Player *currentPlayer, Card drawnCard)
{
    int i;

    // Add drawn card to score pile
    currentPlayer->scorePile.cards[emptyCardIndex(currentPlayer->scorePile)] = drawnCard;
    currentPlayer->scorePile.cardCount++;

    // Add cards from tank with same color to score pile
    for (i = 0; i < currentPlayer->tank.cardCount; i++)
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
 * @return void
 */
void addToTank(Player *currentPlayer, Card drawnCard)
{
    currentPlayer->tank.cards[emptyCardIndex(currentPlayer->tank)] = drawnCard;
    currentPlayer->tank.cardCount++;
    colorCount(&currentPlayer->tank, drawnCard.front, INCREMENT);
}

/**
 * Steals the cards from the stolen player's tank to the current player's tank
 * @param currentPlayer A pointer to the current player's structure containing the player data
 * @param currentPlayer A pointer to the stolen player's structure containing the player data
 * @param drawnCard The color of the drawn card
 * @return void
 */
void stealTank(Player *currentPlayer, Player *stolenPlayer, Color drawnCard)
{
    int i;

    // Add cards from tank with same color to score pile
    for (i = 0; i < stolenPlayer->tank.cardCount; i++)
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
 * Shifts cards in a deck to fill a gap left by a removed card
 * @param deck The deck structure to be modified
 * @param removedCardIndex The index of the card that was removed
 * @return void
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
        // pauseScreen(1.0);
        printf(".");
    }
    printf("\n");
    displayCard(drawnCard, BIG, FRONT);
    printf("Drawn card worth (%d pt/s)!\n", drawnCard.points);
}

/**
 * Checks the tank if there are cards with the same color as drawn card 
 * @param m A pointer to the game structure containing the game data
 * @param tank Cards in the player's tank
 * @return void
 */
void checkSameColor(Game *m, Deck tank)
{
    int i;

    m->sameColorCount = 0;
    m->sameColorPoints = 0;

    for (i = 0; i < tank.cardCount; i++)
    {
        if (tank.cards[i].front == m->drawnCard.front)
        {
            m->sameColorCount++;
            m->sameColorPoints += tank.cards[i].points;
        }
    }
}

/**
 * Increments or decrements the color count of the deck
 * @param currentDeck A pointer to the current deck's structure containing the deck data
 * @param currentCard The color of the current card
 * @param mode The operation mode (INCREMENT or DECREMENT)
 * @return void
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
 * Calculates the total score in the score pile
 * @param currentPlayer A pointer to the current player's structure containing the player data
 * @return void
 */
void calculateScore(Player *currentPlayer)
{
    int i;

    currentPlayer->scorePile.totalScore = 0;

    for (i = 0; i < currentPlayer->scorePile.cardCount; i++)
    {
        currentPlayer->scorePile.totalScore += currentPlayer->scorePile.cards[i].points;
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

#endif // GAME_C