#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    srand(time(NULL));
    int min = 1;
    int max = 10;
    int guesses = 0;
    int userGuess = 0;

    int randomNum = (rand() % (max - min + 1)) + min;

    while (userGuess != randomNum){
        printf("Input a Number between 1 and 10\n");
        fflush(stdout);

        if (scanf("%d", &userGuess) != 1){
            int c;
            while ((c = getchar()) != '\n' && c != EOF); // clear bad input
            printf("That's not a valid number, try again.\n");
            fflush(stdout);
            continue; // skip incrementing guesses, go back to top of loop
        }

        guesses++;
    }

    printf("\nYou needed %d Guesses to guess %d as the random number! ", guesses, randomNum);
    fflush(stdout);
    return 0;
}