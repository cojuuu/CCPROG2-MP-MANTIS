/**
* Description : A text-based recreation of the card game Mantis in C
* Author/s : De Dios, Justin Marco C.
*            Ocampo, Kysha Denise D.
* Section : S12A & S22A
* Last Modified : 03-29-2026
* Acknowledgments : 
* 1. Portfolio Courses - File Access Basics
* Link: https://www.youtube.com/watch?v=HQNsriyMhtY&t=129s
* 2. GeeksforGeeks - How to use memset()
* Link: https://www.geeksforgeeks.org/c/memset-c-example/
* 3. Neso Academy - Pointer to Structure Variable
* Link: https://www.youtube.com/watch?v=VsnXsfNstVw
* 4. GeeksforGeeks - Bubble Sort Algorithm
* Link: https://www.geeksforgeeks.org/dsa/bubble-sort-algorithm/
* 5. Stack Overflow - Windows API color code
* Link: https://stackoverflow.com/questions/17125440/c-win32-console-color
* 6. GeeksforGeeks - Non-Standard I/O Functions in C
* Link: https://www.geeksforgeeks.org/c/non-standard-input-output-functions-in-c/
* 7. Github - conio.h library alternative for Linux and MacOS
* Link: https://stackoverflow.com/questions/3276546/how-to-implement-getch-function-of-c-in-linux/23035044#23035044
* 8. Patorjk - Text to graffiti ASCII art
* Link: https://patorjk.com/software/taag/#p=display&f=Graffiti&t=Type+Something+&x=none&v=4&h=4&w=80&we=false
* 9. ThoughtsOrDiscoveries - Get cursor position in Windows or non-Windows terminal
* Link: https://thoughtsordiscoveries.wordpress.com/2017/04/26/set-and-read-cursor-position-in-terminal-windows-and-linux/#:~:text=April%2026%2C%202017%20April%2026,see%20%5B4%2C5%5D.
*/

/* ----- preprocessor directives ----- */
#include "menu.c"
#include "player.c"
#include "game.c"
#include "game_display.c"
#include "leaderboard.c"
#include "settings.c"
#include "data.c"
#include "random.c"
#include "interface.c"

int main()
{   
    Game m;
    memset(&m, 0, sizeof(m));
    iClear(0, 0, CONSOLE_WIDTH, CONSOLE_HEIGHT);
    mainMenu(&m);

    return 0;
}

/**
* This is to certify that this project is my/our own work, based on my/our personal
* efforts in studying and applying the concepts learned. I/We have constructed the
* functions and their respective algorithms and corresponding code by myself/ourselves.
* The program was run, tested, and debugged by my/our own efforts. I/We further certify
* that I/we have not copied in part or whole or otherwise plagiarized the work of other
* students and/or persons, nor did I employ the use of AI in any part of the deliverable.
*
* De Dios, Justin Marco C. (12504424)
* Ocampo, Kysha Denise D. (12506834)
*/