#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

void countdownTimer(int hours, int minutes, int seconds) 
{
    int totalSeconds = hours * 3600 + minutes * 60 + seconds;
    
    printf("\nCountdown started...\n");
    while (totalSeconds > 0) 
    {
        int h = totalSeconds / 3600;
        int m = (totalSeconds % 3600) / 60;
        int s = totalSeconds % 60;

        printf("\r%02d:%02d:%02d", h, m, s);
        Sleep(1000);
        totalSeconds--;
    }
    printf("\rTime's up! ⏰\n");
    Beep(750, 800);
}

int main() 
{
    int h, m, s;

    printf("Enter time (HH MM SS): ");
    scanf("%d %d %d", &h, &m, &s);

    if (h < 0 || m < 0 || m > 59 || s < 0 || s > 59) 
    {
        printf("Invalid time format!\n");
        return 1;
    }

    countdownTimer(h, m, s);
    return 0;
}
