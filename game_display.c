/**
 * Description : Contains the functions that handles the game display of Mantis
 * Author/s : De Dios, Justin Marco C.
 *            Ocampo, Kysha Denise D.
 *  Section : S12A & S22A
 *  Last Modified : 03-29-2026
 */

#ifndef GAME_DISPLAY_C 
#define GAME_DISPLAY_C 

#include <stdio.h>

#include "defs.h"

/**
 * Displays the winner/s of mantis
 * @param m A pointer to the game structure containing the game data
 * @return void
 */
void displayWinner(Game *m)
{
    int i, j;
    Player temp;

    printGameOver();
    printf("\n  PLAYER                                SCORE\n");
    for (i = 0; i < m->winnerCount; i++)
        printf("  %-36s  %3d pts  <-- WINNER\n", 
            m->activePlayers[m->winner[i]].username, m->activePlayers[m->winner[i]].scorePile.totalPoints);

    for (i = 0; i < m->playerCount; i++)
    {
        for (j = 0; j < m->playerCount - 1; j++)
        {
            if (m->activePlayers[j].scorePile.totalPoints < m->activePlayers[j + 1].scorePile.totalPoints)
            {
                temp = m->activePlayers[j];
                m->activePlayers[j] = m->activePlayers[j + 1];
                m->activePlayers[j + 1] = temp;
            }
        }
    }

    for (i = 0; i < m->playerCount; i++)
    {
        if (m->activePlayers[i].scorePile.totalPoints < m->settings.winningPoints)
        {
            printf("  %-36s  %3d pts\n", 
                m->activePlayers[i].username, m->activePlayers[i].scorePile.totalPoints);
        }
    }
}

/**
 * Prints the current state of all players' tanks and their total scores
 * @param m A pointer to the game structure containing the game data
 * @param playerType ACTIVE - the player taking their turn; INACTIVE - the player who is not currently taking their turn
 * @return void
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
                printf("(%d) %s ", i + 1, m->activePlayers[i].username);
                displayFrontSideDeck(m->activePlayers[i].tank, SMALL);
                printf("\n");
                printf("[Score: %d]\n\n", m->activePlayers[i].scorePile.totalPoints);
            }
        }
    }
    else if (playerType == ACTIVE)
    {
        printf("\n");
        displayFrontSideDeck(m->activePlayers[m->currentPlayer].tank, BIG);
        printf("     (%d) %s  ", m->currentPlayer + 1, m->activePlayers[m->currentPlayer].username);
        printf("[Score]: %d\n", m->activePlayers[m->currentPlayer].scorePile.totalPoints);
    }
}

/**
 * Displays the back-side of the top card in the draw pile and the total deck count
 * @param m A pointer to the game structure containing the game data
 * @return void
 */
void displayTopDeck(Game *m)
{
    printf("[TOP DECK]\n");
    displayCard(m->drawPile.cards[0], BIG, BACK);
    printf("(%d left)\n", m->drawPile.cardCount);
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
 * Displays a single card depending on the user's desired size or desired side
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
 * Displays the deck's front side card
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
 * Prints the "Game Over" screen of Mantis
 * @return void
*/
void printGameOver()
{
    setColor(MAGENTA);
    printf("  /$$$$$$   /$$$$$$  /$$      /$$ /$$$$$$$$        /$$$$$$  /$$    /$$ /$$$$$$$$ /$$$$$$$ \n");
    printf(" /$$__  $$ /$$__  $$| $$$    /$$$| $$_____/       /$$__  $$| $$   | $$| $$_____/| $$__  $$\n");
    printf("| $$  \\__/| $$  \\ $$| $$$$  /$$$$| $$            | $$  \\ $$| $$   | $$| $$      | $$  \\ $$\n");
    printf("| $$ /$$$$| $$$$$$$$| $$ $$ /$$$$| $$$$$         | $$  | $$|  $$ / $$/| $$$$$   | $$$$$$$/\n");
    printf("| $$|_  $$| $$__  $$| $$  $$$| $$| $$__/         | $$  | $$ \\  $$ $$/ | $$__/   | $$__  $$\n");
    printf("| $$  \\ $$| $$  | $$| $$\\  $ | $$| $$            | $$  | $$  \\  $$$/  | $$      | $$  \\ $$\n");
    printf("|  $$$$$$/| $$  | $$| $$ \\/  | $$| $$$$$$$$      |  $$$$$$/   \\  $/   | $$$$$$$$| $$  | $$\n");
    printf(" \\______/ |__/  |__/|__/     |__/|________/       \\______/     \\_/    |________/|__/  |__/\n");
    setColor(WHITE);
}

/**
 * Prints the "Error" screen of Mantis
 * @return void
*/
void printError()
{
    setColor(RED);
    printf(" /$$$$$$$$ /$$$$$$$  /$$$$$$$   /$$$$$$  /$$$$$$$\n"); 
    printf("| $$_____/| $$__  $$| $$__  $$ /$$__  $$| $$__  $$\n");
    printf("| $$      | $$  \\ $$| $$  \\ $$| $$  \\ $$| $$  \\ $$\n");
    printf("| $$$$$   | $$$$$$$/| $$$$$$$/| $$  | $$| $$$$$$$/\n");
    printf("| $$__/   | $$__  $$| $$__  $$| $$  | $$| $$__  $$\n");
    printf("| $$      | $$  \\ $$| $$  \\ $$| $$  | $$| $$  \\ $$\n");
    printf("| $$$$$$$$| $$  | $$| $$  | $$|  $$$$$$/| $$  | $$\n");
    printf("|________/|__/  |__/|__/  |__/ \\______/ |__/  |__/\n");
    setColor(WHITE);
}

/**
 * Navigates the user back to the main menu when the program encounters an error
 * @param m A pointer to the game structure containing the game data
 * @return void
*/
void errorNav(Game *m)
{
    setColor(RED);
    waitEnter("Press enter to go back to the main menu...");
    setColor(WHITE);
    iClear(0, 0, CONSOLE_WIDTH, CONSOLE_HEIGHT);
    memset(m, 0, sizeof(*m));
    mainMenu(m);
}

#endif // LOAD_C;