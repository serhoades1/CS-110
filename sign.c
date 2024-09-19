#include <stdio.h>
#include <string.h>
#include "font5x7.h"


//Initializes the functions so they can be used anywhere
void printChar(char word[], char currChar);
void charCreation(char currentLetter, char symbol);

void addChar(char input[40]) { 
    //Makes an array for each letter individually, then puts them together to make the word
    scanf("%s", input);
    
    //Will print differently depending on which letter is input
    if (input[0] == 'W' || input[0] == 'C') {
        char input2[100];
        char letterArray[20][20];
        int totalWords = 0;
        
        while (scanf("%s", input2) == 1) {
            strcpy(letterArray[totalWords], input2);
            totalWords++;
        }

        printf("\n");

        if (input[0] == 'W') {
            for (int i = 0; i < totalWords; i++) {
                printChar(letterArray[i], input[1]);
            }
        }
        // Else prints the arrays for the C input
        else {
            for (int i = 0; i < totalWords; i++) {
                for (int j = 0; j < strlen(letterArray[i]); j++) {
                    charCreation(letterArray[i][j], input[1]);
                }
                if (i != totalWords - 1 ) {
                    printf("\n");
                    printf("\n");
                    printf("\n");
                    printf("\n");
                    printf("\n");
                    printf("\n");
                    printf("\n");
                    printf("\n");
                }
            }
        }
    }

    else if (input[0] == 'L') {
        char input2[20][100];
        int lineCount = 0;

        getchar();
        // Definitely had to look up some functions online that can be used to do what I need
        // Like strcspn was actually exactly what I needed

        while (fgets(input2[lineCount], sizeof(input2[lineCount]), stdin) != NULL) {
            input2[lineCount][strcspn(input2[lineCount], "\n")] = '\0';
            lineCount++;
        }

        for(int i = 0; i < lineCount; i++) {
            printChar(input2[i], input[1]);
        }
    }
}


void charCreation(char currentLetter, char symbol) {
    // Converts letters to hexadecimals
    // Puts resulting characters into array
    int startingChar = (currentLetter - 32) * 5;
    int hexaDec[5] = {0};
    char bin[8][8];
    for (int i = 0; i < 5; i++) {
        hexaDec[i] = Font5x7[startingChar + i];
    }

    for (int j = 0; j < 7; j++) {
        for (int i = 7; i >= 0; i--) {
            if (j >= 5) {
                bin[j][i] = '0';
            } 
            else {
                bin[j][i] = (hexaDec[j] & 1) + '0';
                hexaDec[j] >>= 1;
            }
        }
    }

    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j <= 7; j++) {
            if (bin[j][i] == '1') {
                // If statement is what prints the characters made of themselves
                if (symbol == '~') {
                    printf("%c", currentLetter);
                } 
                // Else is just everything else that someone could want to print with
                else {
                    printf("%c", symbol);
                }
            } 
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
}


void printChar(char word[], char currChar) {
    // This is where the magic happens
    // Creates a 2D array for each letter and puts them together to form the words
    int alphabet = strlen(word);
    int hexaDec[alphabet][5];
    char bin[8][alphabet][8];

    for (int i = 0; i < alphabet; i++) {
        /* Finds the start value by taking the ACII value and subtracting 32 to get the value
        of the chararacters in the font5x7.h file. This is then multiplied by 5 since the 
        values are paired in sets of 5, since it's a 5x7 format used to make the characters.
        */
        int startValue = (word[i] - 32) * 5;
        for (int j = 0; j < 5; j++) {
            hexaDec[i][j] = Font5x7[startValue + j];
        }
        // startValue is used instead of i so that the number increments by 1 at a time instead of 5
    }
    
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < alphabet; j++) {
            for (int x = 7; x >= 0; x--) {
                if (i >= 5) {
                    bin[i][j][x] = '0';
                } 
                else {
                    bin[i][j][x] = (hexaDec[j][i] & 1) + '0';
                    hexaDec[j][i] >>= 1;
                }
            }
        }
    }

    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j < alphabet; j++) {
            for (int x = 0; x <= 7; x++) {
                if (bin[x][j][i] == '1') {
                    if (currChar == '~') {
                        printf("%c", word[j]);
                    }
                    else {
                        printf("%c", currChar);
                    }
                }
                else {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
}


int main() {
    // Just calls all the above functions
    // Tried to get by with as little use of main() as possible
    // I'm sure the code could be more efficient but that's a problem for another day
    char input[41];
    addChar(input);

    return 0;
}