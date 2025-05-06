#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

void countdownTimer(int hours, int minutes, int seconds) 
{
    int totalSeconds = hours * 3600 + minutes * 60 + seconds;

    printf("\n╔════════════════ Countdown Timer ════════════╗\n");
    printf("║  Timer will run for the specified duration  ║\n");
    printf("╚═════════════════════════════════════════════╝\n");

    while (totalSeconds > 0) 
    {
        int h = totalSeconds / 3600;
        int m = (totalSeconds % 3600) / 60;
        int s = totalSeconds % 60;

        printf("\r⏳ Time Remaining: %02d:%02d:%02d   ", h, m, s);
        fflush(stdout);
        Sleep(1000);
        totalSeconds--;
    }

    // Final output box
    printf("\r╔═════════════════════════════════════════════╗\n");
    printf(  "║              Time's up! ⏰                  ║\n");
    printf(  "╚═════════════════════════════════════════════╝\n");
    
    Beep(750, 800);  // Beep sound
}

int main() 
{
    int h, m, s;

    printf("Enter the time (HH MM SS): ");
    scanf("%d %d %d", &h, &m, &s);

    if (h < 0 || m < 0 || m > 59 || s < 0 || s > 59) 
    {
        printf("Invalid time format!\n");
        return 1;
    }

    countdownTimer(h, m, s);
    return 0;
}
