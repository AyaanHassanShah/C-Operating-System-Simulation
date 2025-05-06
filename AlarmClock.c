#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

void beep() 
{
    Beep(750, 300); // Frequency: 750 Hz, Duration: 300 ms
}

void setAlarm(int hour, int minute) 
{
    printf("Alarm set for %02d:%02d\n", hour, minute);
    while (1) {
        time_t now = time(NULL);
        struct tm *currentTime = localtime(&now);

        if (currentTime->tm_hour == hour && currentTime->tm_min == minute)
         {
            printf("\nALARM!!! Time is %02d:%02d\n", hour, minute);
            beep();
            printf("Press 's' to stop or 'z' to snooze: ");
            char choice;
            while (1) {
                choice = getchar();
                if (choice == 's') 
                {
                    printf("Alarm stopped.\n");
                    return;
                } else if (choice == 'z') {
                    printf("Snoozing for 5 minutes...\n");
                    Sleep(5 * 60 * 1000); // Snooze for 5 minutes
                    break;
                }
            }
        }
        Sleep(1000); // Check every second
    }
}

int main() 
{
    int hour, minute;
    printf("\n\n Clock is set to 24 hour format\n");
    printf("Enter alarm time (HH MM): ");
    if (scanf("%d %d", &hour, &minute) != 2 || hour < 0 || hour > 23 || minute < 0 || minute > 59) {
        printf("Invalid time format. Please use 24-hour format.\n");
        return 1;
    }

    // Clear input buffer
    while (getchar() != '\n');

    setAlarm(hour, minute);

    return 0;
}
