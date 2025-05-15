#include <stdio.h>
#include <stdlib.h>

void displayMenu() {
    printf("\n+--------- Temperature Converter ---------+\n");
    printf("|  1. Celsius to Fahrenheit   (C to F)   |\n");
    printf("|  2. Fahrenheit to Celsius   (F to C)   |\n");
    printf("|  3. Celsius to Kelvin       (C to K)   |\n");
    printf("|  4. Kelvin to Celsius       (K to C)   |\n");
    printf("|  5. Exit                               |\n");
    printf("+-----------------------------------------+\n");
    printf("Enter your choice: ");
}

void celsiusToFahrenheit() {
    float c, f;
    printf("Enter temperature in Celsius (C): ");
    scanf("%f", &c);
    f = (c * 9 / 5) + 32;
    printf("Result: %.2f C = %.2f F\n", c, f);
}

void fahrenheitToCelsius() {
    float f, c;
    printf("Enter temperature in Fahrenheit (F): ");
    scanf("%f", &f);
    c = (f - 32) * 5 / 9;
    printf("Result: %.2f F = %.2f C\n", f, c);
}

void celsiusToKelvin() {
    float c, k;
    printf("Enter temperature in Celsius (C): ");
    scanf("%f", &c);
    k = c + 273.15;
    printf("Result: %.2f C = %.2f K\n", c, k);
}

void kelvinToCelsius() {
    float k, c;
    printf("Enter temperature in Kelvin (K): ");
    scanf("%f", &k);
    c = k - 273.15;
    printf("Result: %.2f K = %.2f C\n", k, c);
}

int main() {
    int choice;

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                celsiusToFahrenheit();
                break;
            case 2:
                fahrenheitToCelsius();
                break;
            case 3:
                celsiusToKelvin();
                break;
            case 4:
                kelvinToCelsius();
                break;
            case 5:
                printf("Exiting Temperature Converter...\n");
                 printf("+----------------------------------------+\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
