#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
    
    srand(time(NULL));

    int min = 5;
    int max = 10;

    int randomNum = (rand() % (max - min + 1))+min;

    printf("%d",randomNum);

    return 0;
}

