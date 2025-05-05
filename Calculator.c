#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void displayMenu() 
{
    printf("\n╔═══════════ Calculator ══════════╗\n");
    printf("║  1. Addition       (+)          ║\n");
    printf("║  2. Subtraction    (-)          ║\n");
    printf("║  3. Multiplication (×)          ║\n");
    printf("║  4. Division       (÷)          ║\n");
    printf("║  5. Exit                        ║\n");
    printf("╚═════════════════════════════════╝\n");
    printf("Enter your choice: ");
}

int main() 
{
    int choice;
    double num1, num2, result;

    while (1) 
    {
        displayMenu();
        scanf("%d", &choice);

        if (choice == 5) 
        {
            printf("\n╔════════════ Goodbye! ═══════════╗\n");
            printf("║    Calculator shutting down...  ║\n");
            printf("╚═════════════════════════════════╝\n");
            break;
        }

        if (choice < 1 || choice > 5) 
        {
            printf("\n❌ Invalid choice! Please try again.\n");
            continue;
        }

        printf("\nEnter first number: ");
        scanf("%lf", &num1);
        printf("Enter second number: ");
        scanf("%lf", &num2);

        printf("\n╔═══════ Calculation Result ═══════╗\n");
        switch (choice)
         {
            case 1:
                result = num1 + num2;
                printf("║  %.2lf + %.2lf = %.2lf          ║\n", num1, num2, result);
                break;
            case 2:
                result = num1 - num2;
                printf("║  %.2lf - %.2lf = %.2lf          ║\n", num1, num2, result);
                break;
            case 3:
                result = num1 * num2;
                printf("║  %.2lf × %.2lf = %.2lf          ║\n", num1, num2, result);
                break;
            case 4:
                if (num2 == 0) {
                    printf("║  Error: Division by zero! ❌     ║\n");
                } else {
                    result = num1 / num2;
                    printf("║  %.2lf ÷ %.2lf = %.2lf          ║\n", num1, num2, result);
                }
                break;
        }
        printf("╚═════════════════════════════════╝\n");
    }

    return 0;
}