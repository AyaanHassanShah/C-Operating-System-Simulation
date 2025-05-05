#include <windows.h>
#include <stdio.h>
#include <conio.h>

void moveCursor(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

void showBatteryBar(int level) 
{
    printf("\n╔══════════ Battery Status ══════════╗\n");
    printf("║ Level: [");
    
    int blocks = level / 10;
    for(int i = 0; i < 10; i++) {
        printf(i < blocks ? "█" : "░");
    }
    printf("] %3d%% ║\n", level);
    printf("╚═══════════════════════════════════╝\n");
}

int main() 
{
    SYSTEM_POWER_STATUS status;
    int timeLeft = 10;
    DWORD lastTime = GetTickCount();

    // Initial screen setup
    system("cls");
    printf("\033[?25l");  // Hide cursor

    while (timeLeft > 0) 
    {
        moveCursor(0, 0);
        printf("Battery Monitor (%d seconds)\n", timeLeft);

        if (GetSystemPowerStatus(&status)) 
        {
            int batteryLevel = status.BatteryLifePercent;
            if (batteryLevel != 255) 
            {
                showBatteryBar(batteryLevel);
                printf("\nStatus: %s", 
                    status.ACLineStatus == 1 ? "🔌 Charging" : "🔋 Battery");
            }
        }

        if (GetTickCount() - lastTime >= 1000) 
        {
            timeLeft--;
            lastTime = GetTickCount();
        }

        if (_kbhit() && _getch() == 27) break;  // ESC to exit

        Sleep(100);
    }

    printf("\033[?25h");  // Show cursor
    return 0;
}