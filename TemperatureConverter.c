#include <stdio.h>

void celsiusToFahrenheit() 
{
    double celsius, fahrenheit;
    printf("Enter temperature in Celsius: ");
    scanf("%lf", &celsius);
    fahrenheit = (celsius * 9 / 5) + 32;
    printf("Temperature in Fahrenheit: %.2lf\n", fahrenheit);
}

void fahrenheitToCelsius() 
{
    double fahrenheit, celsius;
    printf("Enter temperature in Fahrenheit: ");
    scanf("%lf", &fahrenheit);
    celsius = (fahrenheit - 32) * 5 / 9;
    printf("Temperature in Celsius: %.2lf\n", celsius);
}

void celsiusToKelvin() 
{
    double celsius, kelvin;
    printf("Enter temperature in Celsius: ");
    scanf("%lf", &celsius);
    kelvin = celsius + 273.15;
    printf("Temperature in Kelvin: %.2lf\n", kelvin);
}

void kelvinToCelsius() 
{
    double kelvin, celsius;
    printf("Enter temperature in Kelvin: ");
    scanf("%lf", &kelvin);
    celsius = kelvin - 273.15;
    printf("Temperature in Celsius: %.2lf\n", celsius);
}

int main() 
{
    int choice;

    do 
    {
        printf("\nTemperature Converter\n");
        printf("1. Celsius to Fahrenheit\n");
        printf("2. Fahrenheit to Celsius\n");
        printf("3. Celsius to Kelvin\n");
        printf("4. Kelvin to Celsius\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
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
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}