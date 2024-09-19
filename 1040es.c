#include <stdio.h>
#include <string.h>

int main() {
    char filingStatus[20];
    int bContinue = 1;
    int income;
    double totalTax;
    
    while (bContinue) {
        printf("----------------------------------\n");
        printf("a. Single\n");
        printf("b. Married filing jointly\n");
        printf("c. Married filing separately\n");
        printf("d. Head of household\n");
        printf("e. Qualifying widow(er)\n");
        printf("----------------------------------\n");
        printf("Enter the filing status (a-e): ");
        scanf(" %s", filingStatus);

        if (strcmp(filingStatus, "a") == 0 || strcmp(filingStatus, "b") == 0 || strcmp(filingStatus, "c") == 0 || strcmp(filingStatus, "d") == 0 || strcmp(filingStatus, "e") == 0) {
            printf("\nEnter the estimated taxable income: ");
            scanf(" %d", &income);
            
            if (income >= 0) {
                if (strcmp(filingStatus, "a") == 0) {
                    if (income <= 11000) {
                        totalTax = income * 0.10;
                    }
                    else if (income <= 44725) {
                        totalTax = 1100 + ((income - 11000) * 0.12);
                    }
                    else if (income <= 95375) {
                        totalTax = 5147 + ((income - 44725) * 0.22);
                    }
                    else if (income <= 182100) {
                        totalTax = 16290 + ((income - 95375) * 0.24);
                    }
                    else if (income <= 231250) {
                        totalTax = 37104 + ((income - 182100) * 0.32);
                    }
                    else if (income <= 578125) {
                        totalTax = 52832 + ((income - 231250) * 0.35);
                    }
                    else {
                        totalTax = 174238.25 + ((income - 578125) * 0.37);
                    }
                }
                else if (strcmp(filingStatus, "b") == 0 || strcmp(filingStatus, "e") == 0) {
                    if (income <= 22000) {
                        totalTax = income * 0.10;
                    }
                    else if (income <= 89450) {
                        totalTax = 2200 + ((income - 22000) * 0.12);
                    }
                    else if (income <= 190750) {
                        totalTax = 10294 + ((income - 89450) * 0.22);
                    }
                    else if (income <= 364200) {
                        totalTax = 32580 + ((income - 190750) * 0.24);
                    }
                    else if (income <= 462500) {
                        totalTax = 74208 + ((income - 364200) * 0.32);
                    }
                    else if (income <= 693750) {
                        totalTax = 105664 + ((income - 462500) * 0.35);
                    }
                    else {
                        totalTax = 186601.50 + ((income - 693750) * 0.37);
                    }
                }
                else if (strcmp(filingStatus, "c") == 0) {
                    if (income <= 11000) {
                        totalTax = income * 0.1;
                    }
                    else if (income <= 44725) {
                        totalTax = 1100 + ((income - 11000) * 0.12);
                    }
                    else if (income <= 95375) {
                        totalTax = 5147 + ((income - 44725) * 0.22);
                    }
                    else if (income <= 182100) {
                        totalTax = 16290 + ((income - 95375) * 0.24);
                    }
                    else if (income <= 231250) {
                        totalTax = 37104 + ((income - 182100) * 0.32);
                    }
                    else if (income <= 346875) {
                        totalTax = 52832 + ((income - 231250) * 0.35);
                    }
                    else {
                        totalTax = 93300.75 + ((income - 346875) * 0.37);
                    }
                }
                else {
                    if (income <= 15700) {
                        totalTax = income * 0.10;
                    }
                    else if (income <= 59850) {
                        totalTax = 1570 + ((income - 15700) * 0.12);
                    }
                    else if (income <= 95350) {
                        totalTax = 6868 + ((income - 59850) * 0.22);
                    }
                    else if (income <= 182100) {
                        totalTax = 14678 + ((income - 95350) * 0.24);
                    }
                    else if (income <= 231250) {
                        totalTax = 35498 + ((income - 182100) * 0.32);
                    }
                    else if (income <= 578100) {
                        totalTax = 51226 + ((income - 231250) * 0.35);
                    }
                    else {
                        totalTax = 172623.50 + ((income - 578100) * 0.37);
                    }
                }
            }
            else {
                printf("No negative income allowed. Income set to zero\n\n");
                income = 0;
                totalTax = 0.00;
            }

            printf("The estimated tax is %.2lf\n\n\n", totalTax);
        }

        else {
            printf("Invalid filing status. Try again.\n\n");
            continue;
        }



        while (bContinue) {
            printf("Continue with another taxpayer (yes or no)? ");
            char answer[20];
            scanf(" %s", answer);
            if (strcmp(answer, "yes") == 0) {
                printf("\n");
                break;
            }
            else if (strcmp(answer, "no") == 0) {
                printf("\n");
                printf("Goodbye.");
                bContinue = 0;
                break;
            }
            else {
                printf("Invalid answer. Try again.\n\n");
                continue;
            }
        }
    }
    
    return 0;
}