/**
* Description : <short description of the project>
* Author/s : De Dios, Justin Marco C.
*            Ocampo, Kysha Denise D.
* Section : S12A & S22A
* Last Modified : 02-01-2026
* Acknowledgments : <list of references used in the making of this project>
*/

/* ----- preprocessor directives ----- */
#include <stdio.h>

#include "functions.c"

int main()
{
    int option;

    displayMainMenu();
    do
    {
        askInput(&option);

        // Input Validation
        if (option != 0 && option != 1 && option != 2 && option !=3)
            printf("Please select a valid option.");
    } while (option != 0 && option != 1 && option != 2 && option !=3);
    
    // New Game
    if (option == 1)
    {

    }
    // Top Players
    else if (option == 2)
    {

    }
    // Settings
    else if (option == 3)
    {

    }
    // Exit
    else if (option == 0)
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
