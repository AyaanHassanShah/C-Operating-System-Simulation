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

DWORD WINAPI alarm_thread(LPVOID arg) {
    while (1) {
        WaitForSingleObject(alarmState.mutex, INFINITE);
        
        if (alarmState.isActive) {
            time_t now = time(NULL);
            struct tm *currentTime = localtime(&now);

            if (currentTime->tm_hour == alarmState.hour && 
                currentTime->tm_min == alarmState.minute) {
                
                system("cls");
                printf("\nALARM TIME: %02d:%02d\n", alarmState.hour, alarmState.minute);
                printf("Press 'S' to stop or 'Z' to snooze\n");
                ReleaseMutex(alarmState.mutex);

                while (1) {
                    beep();
                    if (_kbhit()) {
                        char choice = _getch();
                        if (choice == 's' || choice == 'S') {
                            printf("\nAlarm stopped!\n");
                            alarmState.isActive = 0;
                            return 0;
                        }
                        if (choice == 'z' || choice == 'Z') {
                            printf("\nSnoozing for %d minutes...\n", SNOOZE_MINUTES);
                            alarmState.minute = (alarmState.minute + SNOOZE_MINUTES) % 60;
                            if (alarmState.minute < SNOOZE_MINUTES) {
                                alarmState.hour = (alarmState.hour + 1) % 24;
                            }
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
    printf("Alarm is running in background. You can continue with other tasks.\n");
    
    // Wait for alarm thread to finish
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);
}

int main() {
    // Initialize mutex
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
    while (getchar() != '\n');  // Clear input buffer

    setAlarm(hour, minute);
    
    // Cleanup
    CloseHandle(alarmState.mutex);
    return 0;
}
