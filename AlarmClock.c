#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

typedef struct {
    int hour;
    int minute;
    int isActive;
    HANDLE mutex;
} AlarmState;

AlarmState alarmState;

#define BEEP_INTERVAL 1000
#define BEEP_FREQUENCY 750
#define BEEP_DURATION 300
#define SNOOZE_MINUTES 5
#define CLEAR_SCREEN() system("cls")

void beep() {
    Beep(BEEP_FREQUENCY, BEEP_DURATION);
}

// Function to bring window to foreground
void bringToForeground() {
    HWND hwnd = GetConsoleWindow();
    if (hwnd) {
        // Get the current window state
        WINDOWPLACEMENT wp = {0};
        wp.length = sizeof(WINDOWPLACEMENT);
        GetWindowPlacement(hwnd, &wp);
        
        // If window is minimized, restore it
        if (wp.showCmd == SW_SHOWMINIMIZED) {
            ShowWindow(hwnd, SW_RESTORE);
        }
        
        // Bring window to foreground
        SetForegroundWindow(hwnd);
        SetActiveWindow(hwnd);
        SetFocus(hwnd);
        
        // Flash the window to get attention
        FlashWindow(hwnd, TRUE);
    }
}

DWORD WINAPI alarm_thread(LPVOID arg) {
    while (1) {
        WaitForSingleObject(alarmState.mutex, INFINITE);
        
        if (alarmState.isActive) {
            time_t now = time(NULL);
            struct tm *currentTime = localtime(&now);

            if (currentTime->tm_hour == alarmState.hour && 
                currentTime->tm_min == alarmState.minute) {
                
                // Bring window to foreground when alarm rings
                bringToForeground();
                
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                CONSOLE_SCREEN_BUFFER_INFO csbi;
                GetConsoleScreenBufferInfo(hConsole, &csbi);
                
                printf("\n\n+-------- ALARM! --------+\n");
                printf("| Time: %02d:%02d           |\n", alarmState.hour, alarmState.minute);
                printf("| S - Stop, Z - Snooze   |\n");
                printf("+----------------------+\n");
                
                ReleaseMutex(alarmState.mutex);

                while (1) {
                    beep();
                    if (_kbhit()) {
                        char choice = _getch();
                        if (choice == 's' || choice == 'S') {
                            alarmState.isActive = 0;
                            printf("\nAlarm stopped!\n");
                            Sleep(1000);
                            return 0;
                        }
                        if (choice == 'z' || choice == 'Z') {
                            alarmState.minute = (alarmState.minute + SNOOZE_MINUTES) % 60;
                            if (alarmState.minute < SNOOZE_MINUTES) {
                                alarmState.hour = (alarmState.hour + 1) % 24;
                            }
                            printf("\nSnoozing for %d minutes...\n", SNOOZE_MINUTES);
                            Sleep(1000);
                            break;
                        }
                    }
                    Sleep(BEEP_INTERVAL);
                }
                continue;
            }
        }
        ReleaseMutex(alarmState.mutex);
        Sleep(1000);
    }
    return 0;
}

void setAlarm(int hour, int minute) {
    WaitForSingleObject(alarmState.mutex, INFINITE);
    alarmState.hour = hour;
    alarmState.minute = minute;
    alarmState.isActive = 1;
    ReleaseMutex(alarmState.mutex);

    HANDLE hThread = CreateThread(NULL, 0, alarm_thread, NULL, 0, NULL);
    if (hThread == NULL) {
        printf("Failed to create alarm thread!\n");
        return;
    }

    printf("Alarm set for %02d:%02d\n", hour, minute);
    printf("Press ESC to exit the alarm program.\n");
    
    // Keep the main thread running
    while (1) {
        if (_kbhit() && _getch() == 27) { // ESC key
            break;
        }
        Sleep(100);
    }
    
    // Clean up
    WaitForSingleObject(alarmState.mutex, INFINITE);
    alarmState.isActive = 0;
    ReleaseMutex(alarmState.mutex);
    
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);
}

int main() {
    // Set console title to make it easier to find the window
    SetConsoleTitle("Alarm Clock");
    
    alarmState.mutex = CreateMutex(NULL, FALSE, NULL);
    if (alarmState.mutex == NULL) {
        printf("Failed to create mutex!\n");
        return 1;
    }

    int hour, minute;
    printf("Enter alarm time (HH MM): ");
    if (scanf("%d %d", &hour, &minute) != 2 || 
        hour < 0 || hour > 23 || 
        minute < 0 || minute > 59) {
        printf("Invalid time format. Please use 24-hour format.\n");
        CloseHandle(alarmState.mutex);
        return 1;
    }
    while (getchar() != '\n');

    setAlarm(hour, minute);
    
    CloseHandle(alarmState.mutex);
    return 0;
}
