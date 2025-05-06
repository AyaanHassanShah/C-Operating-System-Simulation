#include <stdio.h>

void celsiusToFahrenheit() 
{
    double celsius, fahrenheit;
    printf("\nEnter temperature in Celsius: ");
    scanf("%lf", &celsius);
    fahrenheit = (celsius * 9 / 5) + 32;

    printf("\n╔════════════════════════════════════════╗\n");
    printf("║  %.2lf°C = %.2lf°F                     ║\n", celsius, fahrenheit);
    printf("╚════════════════════════════════════════╝\n");
}

void fahrenheitToCelsius() 
{
    double fahrenheit, celsius;
    printf("\nEnter temperature in Fahrenheit: ");
    scanf("%lf", &fahrenheit);
    celsius = (fahrenheit - 32) * 5 / 9;

    printf("\n╔════════════════════════════════════════╗\n");
    printf("║  %.2lf°F = %.2lf°C                     ║\n", fahrenheit, celsius);
    printf("╚════════════════════════════════════════╝\n");
}

void celsiusToKelvin() 
{
    double celsius, kelvin;
    printf("\nEnter temperature in Celsius: ");
    scanf("%lf", &celsius);
    kelvin = celsius + 273.15;

    printf("\n╔════════════════════════════════════════╗\n");
    printf("║  %.2lf°C = %.2lfK                     ║\n", celsius, kelvin);
    printf("╚════════════════════════════════════════╝\n");
}

void kelvinToCelsius() 
{
    double kelvin, celsius;
    printf("\nEnter temperature in Kelvin: ");
    scanf("%lf", &kelvin);
    celsius = kelvin - 273.15;

    printf("\n╔════════════════════════════════════════╗\n");
    printf("║  %.2lfK = %.2lf°C                     ║\n", kelvin, celsius);
    printf("╚════════════════════════════════════════╝\n");
}

void showMenu()
{
    printf("\n╔════════════ Temperature Converter ═══════════╗\n");
    printf("║  1. Celsius to Fahrenheit                    ║\n");
    printf("║  2. Fahrenheit to Celsius                    ║\n");
    printf("║  3. Celsius to Kelvin                        ║\n");
    printf("║  4. Kelvin to Celsius                        ║\n");
    printf("║  5. Exit                                     ║\n");
    printf("╚══════════════════════════════════════════════╝\n");
    printf("Enter your choice: ");
}

int main() 
{
    int choice;

    printf("╔════════════════════════════════════════════╗\n");
    printf("║     🌡️ Welcome to Temperature Converter     ║\n");
    printf("╚════════════════════════════════════════════╝\n");

    do 
    {
        showMenu();
        scanf("%d", &choice);

        switch (choice) 
        {
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
                printf("\n╔════════════════════════════════════════════╗\n");
                printf("║      👋 Exiting Temperature Converter      ║\n");
                printf("╚════════════════════════════════════════════╝\n");
                break;
            default:
                printf("\n❌ Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
