#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // for sleep()

void showBatteryBar(int level) {
    int blocks = level / 10;

    printf("🔋 Battery: [");
    for (int i = 0; i < blocks; i++) {
        printf("█");
    }
    for (int i = blocks; i < 10; i++) {
        printf(" ");
    }
    printf("] %d%%\n", level);
}

int main() {
    SYSTEM_POWER_STATUS status;

    while (1) {
        system("cls");  // clear console

        printf("╔════════════════════════════════════════╗\n");
        printf("║    🎯 Live Battery Monitor (Windows)   ║\n");
        printf("╚════════════════════════════════════════╝\n\n");

        if (GetSystemPowerStatus(&status)) {
            int batteryLevel = status.BatteryLifePercent;

            if (batteryLevel != 255) {  // 255 means unknown
                showBatteryBar(batteryLevel);

                if (status.ACLineStatus == 1)
                    printf("\n⚡ Status: 🔌 Charging\n");
                else if (status.ACLineStatus == 0)
                    printf("\n⚡ Status: 🔋 Discharging\n");
                else
                    printf("\n⚡ Status: ❓ Unknown\n");

            } else {
                printf("❌ Battery information not available.\n");
            }
        } else {
            printf("❌ Failed to get power status.\n");
        }

        sleep(2); // 2 second delay
    }

    return 0;
}


