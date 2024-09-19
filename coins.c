#include <stdio.h>
#include <math.h>

int main() {
    int numPennies;
    int numNickels;
    int numDimes;
    int numQuarters;

    printf("Enter the number of quarters: ");
    scanf("%d", &numQuarters);
    printf("Enter the number of dimes: ");
    scanf("%d", &numDimes);
    printf("Enter the number of nickels: ");
    scanf("%d", &numNickels);
    printf("Enter the number of pennies: ");
    scanf("%d", &numPennies);

    int totalDollars = ((numQuarters * 25) + (numDimes * 10) + (numNickels * 5) + (numPennies)) / 100;
    int totalCents = ((numQuarters * 25) + (numDimes * 10) + (numNickels * 5) + (numPennies)) % 100;
    double totalWeight = ((numQuarters * 5.67) + (numDimes * 2.268) + (numNickels * 5.0) + (numPennies * 2.5)) * 0.00220462; //Converts total weight in grams to pounds
    int numWheelbarrows = (totalWeight / 300) + 1; // + 1 rounds the number up

    printf("\nTotal value is %d dollars and %d cents.\n", totalDollars, totalCents);
    printf("Total weight of coins is %lf pounds.\n", totalWeight);
    printf("It needs %d wheelbarrows to transport the coins.\n", numWheelbarrows);
    printf("%d dollars of coins can be exchanged for the following paper bills:\n", totalDollars);

    int numTwenties = totalDollars / 20;
    int remainingMoney = totalDollars % 20;
    int numTens = remainingMoney / 10;
    remainingMoney = remainingMoney % 10;
    int numFives = remainingMoney / 5;
    remainingMoney = remainingMoney % 5;
    int numOnes = remainingMoney;

    printf("\t%d twenty-dollar bills\n", numTwenties);
    printf("\t%d ten-dollar bills\n", numTens);
    printf("\t%d five-dollar bills\n", numFives);
    printf("\t%d one-dollar bills\n", numOnes);

    double billWeight = (numTwenties + numTens + numFives + numOnes) * 0.00220462;

    printf("The weight of paper bills is only %lf pounds.", billWeight);
}