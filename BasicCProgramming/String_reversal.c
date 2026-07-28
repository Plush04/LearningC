#include <stdio.h>
#include <string.h>

int main(){
    
    char word[30];
    int i;
    printf("Type a word \n");
    scanf("%s", word);
    int wordLength = strlen(word);

    char reversedWord[30];

    for (i = 0; i < wordLength; i++){
        int indexForPrint = wordLength - i - 1 ;
        reversedWord[i] = word[indexForPrint];

    }

    reversedWord[wordLength] = '\0'; 
    int result = strcmp(word,reversedWord);
    if (result == 0){
        printf("This word is a palindrome!");
    }
    else{
        printf("The words are different, this is the reversed word: %s", reversedWord);
    }

}