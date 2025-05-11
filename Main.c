#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "../include/PCB.h"

#define ADMIN_PASS "admin123"
#define MAX_TRIES 3
#define USER 0
#define KERNEL 1
#define USER_MODE_MENU 1
#define KERNEL_MODE_MENU 2

typedef struct {
    int Mode;
    int Auth;
    char Username[50];
} SystemState;

int TotalRam;
int TotalHdd;
int CpuCores;
int AvailableRam;
int Pid = 0;
SystemState State = {USER, 0, "guest"};
HANDLE pcbMutex; // Global mutex variable

// Function declarations
void Boot_Sequence(void);
void Input_Specs(void);
void Display_Welcome(void);
void SwitchToKernel(void);
void ShowSystemStatus(void);
void ShowUserMenu(void);
void ShowKernelMenu(void);
void KillTask(void);
void MinimizeTask(void);
void MaximizeTask(void);
void DeleteUserFile(void);
void ShowResourceUsage(void);
void LaunchTask(const char* TaskName, int MemSize);
void ShowRealTimeClock();

void Boot_Sequence() {
    char loading[] = {'|', '/', '-', '\\'};
    
    printf("\n╔══════════ System Initialization ══════════╗\n");
    printf("║                                           ║\n");
    for(int i = 0; i < 20; i++) {
        printf("\r║     Booting up... %c                    ║", loading[i % 4]);
        Sleep(100);
    }
    printf("\r║           System Boot Complete!           ║\n");
    printf("╚═══════════════════════════════════════════╝\n");
    
    printf("\n╔═════════ Loading Components ═════════════╗\n");
    printf("║                                          ║\n");
    printf("║    CPU  ");
    for(int i = 0; i < 20; i++) {
        printf("█");
        Sleep(50);
    }
    printf(" ✓           ║\n");
    
    printf("║    RAM  ");
    for(int i = 0; i < 20; i++) {
        printf("█");
        Sleep(50);
    }
    printf(" ✓           ║\n");
    
    printf("║    HDD  ");
    for(int i = 0; i < 20; i++) {
        printf("█");
        Sleep(50);
    }
    printf(" ✓           ║\n");
    printf("║                                          ║\n");
    printf("╚══════════════════════════════════════════╝\n");
    Sleep(500);
}

void Input_Specs() {
    printf("\n╔═══════ Enter System Specifications ═══════╗\n");
    printf("║                                           ║\n");
    printf("    Enter total RAM (GB): ");
    scanf("%d", &TotalRam);
    printf("    Enter total HDD (GB): ");
    scanf("%d", &TotalHdd);
    printf("    Enter number of CPU cores: ");
    scanf("%d", &CpuCores);
    printf("║                                           ║\n");
    printf("╚═══════════════════════════════════════════╝\n");
}

void ShowRealTimeClock() {
   
    SYSTEMTIME st;
    char timeStr[100];
    char dateStr[100];
    
    printf("\n╔═══════════ System Clock ═════════════╗\n");
    printf("║ Displaying current time for 10s...   ║\n");
    printf("╚══════════════════════════════════════╝\n");
    Sleep(1000);
    
    for(int i = 0; i < 10; i++) {
        GetLocalTime(&st);
        
        // Format time with AM/PM
        sprintf(timeStr, "%02d:%02d:%02d %s", 
                (st.wHour > 12) ? st.wHour - 12 : (st.wHour == 0) ? 12 : st.wHour,
                st.wMinute, 
                st.wSecond,
                (st.wHour >= 12) ? "PM" : "AM");
                
        // Format date
        sprintf(dateStr, "%04d-%02d-%02d", st.wYear, st.wMonth, st.wDay);
        system("cls");
        printf("\r╔═══════════ System Clock ═══════════╗\n");
        printf("║ Time: %-20s         ║\n", timeStr);
        printf("║ Date: %-20s         ║\n", dateStr);
        printf("╚════════════════════════════════════╝\n");
        
        Sleep(1000);  // Update every second
        system("cls"); // Clear screen for next update
    }
}

void Display_Welcome() {
    printf("\n╔══════════ System Specifications ═════════╗\n");
    printf("║                                          ║\n");
    printf("║    Memory (RAM)  : %6d Gigabytes      ║\n", TotalRam);
    printf("║    Storage (HDD) : %6d Gigabytes      ║\n", TotalHdd);
    printf("║    CPU Cores     : %6d Cores          ║\n", CpuCores);
    printf("║                                          ║\n");
    printf("╚══════════════════════════════════════════╝\n");
}

void SwitchToKernel() 
{
    char Pass[50];
    int Tries = 0;

    while (Tries < MAX_TRIES) 
    {
        printf("\n╔═════════ Kernel Access Authentication ═════════╗\n");
        printf("║ User: %-18s                       ║\n", State.Username);
        printf("║ Enter password (try %d/%d):                      ║\n", Tries + 1, MAX_TRIES);
        printf("╚════════════════════════════════════════════════╝\n");
        printf(" Password: ");
        scanf("%s", Pass);

        if (strcmp(Pass, ADMIN_PASS) == 0) 
        {
            State.Mode = KERNEL;
            State.Auth = 1;
            strcpy(State.Username, "admin");
            printf("\n╔═════════ Access Granted ═════════╗\n");
            printf("║ Switching to Kernel Mode...      ║\n");
            printf("╚══════════════════════════════════╝\n");
            Sleep(1000);
            return;
        }
        Tries++;
        printf("\n╔═════════ Access Denied ═════════╗\n");
        printf("║ Invalid password!              ║\n");
        printf("╚══════════════════════════════════╝\n");
    }
    printf("\n╔═════════ Security Alert ═════════╗\n");
    printf("║ Too many failed attempts!       ║\n");
    printf("║ Access locked for 30 seconds    ║\n");
    printf("╚══════════════════════════════════╝\n");
    
    // Add delay after too many attempts
    for (int i = 30; i > 0; i--) {
        printf("\rLocked for %d seconds... ", i);
        Sleep(1000);
    }
    printf("\rAccess restriction lifted.       \n");
}

void ShowSystemStatus() 
{
    // Calculate memory usage statistics
    int totalRAMKB = TotalRam * 1024 * 1024;
    int usedRAMKB = totalRAMKB - AvailableRam;
    float ramUsagePercent = ((float)usedRAMKB / totalRAMKB) * 100;
    
    printf("\n╔═══════════ System Status ════════════╗\n");
    printf("║ Mode: %-12s                   ║\n", State.Mode == KERNEL ? "Kernel" : "User");
    printf("║ User: %-12s                   ║\n", State.Username);
    printf("║                                      ║\n");
    printf("║ Hardware Resources:                  ║\n");
    printf("║ Total RAM:    %6d GB              ║\n", TotalRam);
    printf("║ Used RAM:     %6d KB (%3.1f%%)       ║\n", usedRAMKB, ramUsagePercent);
    printf("║ Free RAM:     %6d KB (%3.1f%%)    ║\n", AvailableRam, 100-ramUsagePercent);
    printf("║ Total HDD:    %6d GB              ║\n", TotalHdd);
    printf("║ CPU Cores:    %6d                 ║\n", CpuCores);
    printf("║                                      ║\n");
    printf("║ Process Information:                 ║\n");
    printf("║ Running Tasks:%6d                 ║\n", Get_Process_Count());
    printf("║ Next PID:     %6d                 ║\n", Pid);
    printf("╚══════════════════════════════════════╝\n");
}

void ShowUserMenu() 
{
    int choice;
    while (1) 
    {
        ShowSystemStatus();
        
        printf("\n╔═══════════ User Mode Tasks ═══════════════╗\n");
        printf("║  1. Alarm Clock (2 MB)                    ║\n");
        printf("║  2. Battery Status (1 MB)                 ║\n");
        printf("║  3. Calculator (2 MB)                     ║\n");
        printf("║  4. Calendar (3 MB)                       ║\n");
        printf("║  5. Chrome (512 MB)                       ║\n");
        printf("║  6. Countdown Timer (2 MB)                ║\n");
        printf("║  7. Mini File Explorer (4 MB)             ║\n");
        printf("║  8. Notepad (4 MB)                        ║\n");
        printf("║  9. Simple Task Manager (3 MB)            ║\n");
        printf("║ 10. Snake Game (2 MB)                     ║\n");
        printf("║ 11. Temperature Converter (1 MB)          ║\n");
        printf("║ 12. TicTacToe (2 MB)                      ║\n");
        printf("║ 13. Todo List (2 MB)                      ║\n");
        printf("║ 14. Typing Speed (2 MB)                   ║\n");
        printf("║ 15. Xor Cipher (1 MB)                     ║\n");
        printf("║                                           ║\n");
        printf("║ -- Process Management --                  ║\n");
        printf("║ 16. Show Running Tasks                    ║\n");
        printf("║ 17. Minimize a Task                       ║\n");
        printf("║ 18. Maximize a Task                       ║\n");
        printf("║                                           ║\n");
        printf("║ -- System Options --                      ║\n");
        printf("║ 19. Switch to Kernel Mode                 ║\n");
        printf("║  0. Exit                                  ║\n");
        printf("╚═══════════════════════════════════════════╝\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if (choice == 0) return;
        if (choice == 16) {
            Display_PCBs();
            continue;
        }
        if (choice == 17) {
            MinimizeTask();
            continue;
        }
        if (choice == 18) {
            MaximizeTask();
            continue;
        }
        if (choice == 19) {
            SwitchToKernel();
            if (State.Mode == KERNEL) {
                ShowKernelMenu();
            }
            continue;
        }

        if (choice >= 1 && choice <= 15) {
            int memSize;
            switch (choice) 
            {
                case 1: memSize = 2048; LaunchTask("AlarmClock", memSize); break;      // 2 MB
                case 2: memSize = 1024; LaunchTask("BatteryStatus", memSize); break;   // 1 MB
                case 3: memSize = 2048; LaunchTask("Calculator", memSize); break;       // 2 MB
                case 4: memSize = 3072; LaunchTask("Calendar", memSize); break;         // 3 MB
                case 5: memSize = 524288; LaunchTask("Chrome", memSize); break;         // 512 MB
                case 6: memSize = 2048; LaunchTask("CountdownTimer", memSize); break;   // 2 MB
                case 7: memSize = 4096; LaunchTask("MiniFileExplorer", memSize); break; // 4 MB
                case 8: memSize = 4096; LaunchTask("Notepad", memSize); break;          // 4 MB
                case 9: memSize = 3072; LaunchTask("SimpleTaskManager", memSize); break;// 3 MB
                case 10: memSize = 2048; LaunchTask("SnakeGame", memSize); break;       // 2 MB
                case 11: memSize = 1024; LaunchTask("TemperatureConverter", memSize); break; // 1 MB
                case 12: memSize = 2048; LaunchTask("TicTacToe", memSize); break;       // 2 MB
                case 13: memSize = 2048; LaunchTask("TodoList", memSize); break;        // 2 MB
                case 14: memSize = 2048; LaunchTask("TypingSpeed", memSize); break;     // 2 MB
                case 15: memSize = 1024; LaunchTask("Xor_Cipher", memSize); break;      // 1 MB
                default: printf("Invalid choice!\n");
            }
        }
    }
}

void MinimizeTask() {
    int pid;
    Display_PCBs();
    printf("\nEnter PID to minimize: ");
    scanf("%d", &pid);
    
    Minimize_Process(pid);
}

void MaximizeTask() {
    int pid;
    Display_PCBs();
    printf("\nEnter PID to maximize: ");
    scanf("%d", &pid);
    
    Maximize_Process(pid);
}

void ShowKernelMenu() 
{
    int choice;
    while (State.Mode == KERNEL) 
    {
        ShowSystemStatus();
        
        printf("\n╔═══════════ Kernel Mode Menu ═══════════════╗\n");
        printf("║  1. Kill Task                              ║\n");
        printf("║  2. Delete File                            ║\n");
        printf("║  3. Show Resource Usage                    ║\n");
        printf("║  4. Show Running Tasks                     ║\n");
        printf("║  5. Minimize a Task                        ║\n");
        printf("║  6. Maximize a Task                        ║\n");
        printf("║  7. Switch to User Mode                    ║\n");
        printf("║  0. Exit                                   ║\n");
        printf("╚════════════════════════════════════════════╝\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 0: 
                return;
            case 1: 
                KillTask();
                break;
            case 2:
                DeleteUserFile();
                break;
            case 3:
                ShowResourceUsage();
                break;
            case 4:
                Display_PCBs();
                break;
            case 5:
                MinimizeTask();
                break;
            case 6:
                MaximizeTask();
                break;
            case 7:
                State.Mode = USER;
                State.Auth = 0;
                strcpy(State.Username, "guest");
                printf("\n╔═════════ Mode Switched ═════════╗\n");
                printf("║ Now running in User Mode        ║\n");
                printf("╚═════════════════════════════════╝\n");
                Sleep(1000);
                return;
            default:
                printf("Invalid choice!\n");
        }
    }
}

void KillTask() 
{
    int pid;
    Display_PCBs();
    printf("\nEnter PID to kill: ");
    scanf("%d", &pid);
    
    int mem = Get_Process_Memory(pid);
    if (mem > 0) {
        printf("\n╔════════ Process Termination ═══════════╗\n");
        printf("║ Terminating PID: %-3d                  ║\n", pid);
        printf("║ Please wait...                        ║\n");
        
        Remove_Process(pid);  // This now handles window closing
        
        AvailableRam += mem;
        printf("║ Memory Released: %-6d KB            ║\n", mem);
        printf("╚════════════════════════════════════════╝\n");
    }
}

void DeleteUserFile() 
{
    char filename[100];
    printf("\n╔═══════════ File Deletion ══════════════╗\n");
    printf("║ Enter file path: ");
    scanf("%s", filename);
    
    // Add confirmation to prevent accidental deletion
    char confirm;
    printf("║ Are you sure you want to delete %s? (y/n): ", filename);
    scanf(" %c", &confirm);
    
    if (confirm == 'y' || confirm == 'Y') {
        if (remove(filename) == 0) {
            printf("║ File deleted successfully              ║\n");
        } else {
            printf("║ Error: Unable to delete file          ║\n");
        }
    } else {
        printf("║ File deletion cancelled                 ║\n");
    }
    printf("╚════════════════════════════════════════╝\n");
}

void ShowResourceUsage() 
{
    int totalRAMKB = TotalRam * 1024 * 1024;
    int usedRAMKB = totalRAMKB - AvailableRam;
    float ramUsagePercent = ((float)usedRAMKB / totalRAMKB) * 100;
    
    printf("\n╔═══════════ Resource Usage ═══════════════╗\n");
    printf("║ RAM Usage: %d/%d KB (%0.1f%%)           ║\n", 
           usedRAMKB, totalRAMKB, ramUsagePercent);
    
    // Display visual RAM usage bar
    printf("║ [");
    int barWidth = 30;
    int filledWidth = (int)(ramUsagePercent * barWidth / 100);
    
    for (int i = 0; i < barWidth; i++) {
        if (i < filledWidth) {
            printf("█");
        } else {
            printf("░");
        }
    }
    printf("] ║\n");
    
    printf("║ Process Count: %-3d                      ║\n", 
           Get_Process_Count());
           
    // Show CPU usage simulation
    printf("║ CPU Usage: ");
    for(int i = 0; i < 5; i++) {
        printf("\r║ CPU Usage: %d%%                          ║", 30 + rand() % 30);
        Sleep(300);
    }
    printf("\n");
    
    printf("╚════════════════════════════════════════════╝\n");
}

void LaunchTask(const char* TaskName, int MemSize) 
{
    if (MemSize <= AvailableRam) 
    {
        printf("\n╔═══════════ Launching Task ═══════════╗\n");
        printf("║  Starting: %-20s      ║\n", TaskName);
        printf("║  Memory allocated: %-6d KB         ║\n", MemSize);
        
        char Cmd[256];
        // Get current directory
        char CurrentDir[MAX_PATH];
        GetCurrentDirectory(MAX_PATH, CurrentDir);
        
        // Construct command with full path and set window title to match the task name
        // This is important for finding the window later when killing tasks
        snprintf(Cmd, sizeof(Cmd), 
            "start /min cmd /c \"chcp 65001 >nul && "
            "title %s && "
            "cd /d \"%s\" && "
            "Bin\\%s.exe\"", 
            TaskName, CurrentDir, TaskName);
            
        // Create PCB entry for the process
        Create_Process(Pid++, TaskName, AvailableRam, MemSize);
        AvailableRam -= MemSize;
        
        // Launch the process
        STARTUPINFO si = {0};
        PROCESS_INFORMATION pi = {0};
        si.cb = sizeof(si);
        
        // Try to get the process handle for direct termination later
        if (CreateProcess(NULL, Cmd, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
            // Store the process handle in the PCB
            PCB* current = head;
            while (current != NULL) {
                if (strcmp(current->name, TaskName) == 0 && current->pid == (Pid-1)) {
                    current->processHandle = pi.hProcess;
                    break;
                }
                current = current->next;
            }
            // Don't close the handles here - they'll be needed for termination
        } else {
            // Fallback to system() if CreateProcess fails
            system(Cmd);
        }
        
        printf("║                                      ║\n");
        printf("║  Task started successfully!          ║\n");
        printf("╚══════════════════════════════════════╝\n");
        Sleep(500);
    } 
    else 
    {
        printf("\n╔══════════════ Error ══════════════╗\n");
        printf("║   Insufficient memory available!   ║\n");
        printf("║   Available RAM: %-6d KB        ║\n", AvailableRam);
        printf("║   Required RAM: %-6d KB         ║\n", MemSize);
        printf("║                                  ║\n");
        printf("║   Close other tasks to free RAM  ║\n");
        printf("╚══════════════════════════════════════╝\n");
    }
}

void CleanupResources() {
    // Kill all running processes before exiting
    PCB* current = head;
    printf("\n══════════ System Cleanup ═══════════\n");
    printf(" Terminating all processes...        \n");
    
    int count = 0;
    
    while (current != NULL) {
        PCB* temp = current;
        current = current->next;
        
        printf(" Terminating %s (PID %d)           \n", 
               temp->name, temp->pid);
        
        // Use the existing Remove_Process function
        Remove_Process(temp->pid);
        count++;
    }
    
    printf(" %d processes terminated              \n", count);
    printf("═════════════════════════════════════\n");
}

int main() 
{
    system("chcp 65001"); // Set console to UTF-8
    system("cls");
    
    printf("\n╔══════════════════════════════════════════╗\n");
    printf("║             Welcome to LAWS-OS           ║\n");
    printf("╚══════════════════════════════════════════╝\n");
    
    Boot_Sequence();
    Input_Specs();
    ShowRealTimeClock();
    Display_Welcome();
    
    AvailableRam = TotalRam * 1024 * 1024; // Convert GB to KB
    
    // Initialize PCB mutex
    pcbMutex = CreateMutex(NULL, FALSE, NULL);
    if (pcbMutex == NULL) {
        printf("Failed to create PCB mutex!\n");
        return 1;
    }
    
    // Initialize scheduler
    Initialize_Scheduler();
    
    // Create scheduler thread
    HANDLE schedulerThread = CreateThread(NULL, 0, SchedulerThread, NULL, 0, NULL);
    if (schedulerThread == NULL) {
        printf("Failed to create scheduler thread!\n");
        CloseHandle(pcbMutex);
        return 1;
    }
    
    ShowUserMenu();
    
    // Signal scheduler to stop
    scheduler_running = 0;
    
    // Clean up processes before exiting
    CleanupResources();
    
    // Cleanup mutex and scheduler thread
    CloseHandle(pcbMutex);
    CloseHandle(schedulerThread);
    
    printf("\n╔══════════════════════════════════════════╗\n");
    printf("║         Shutting down LAWS-OS...         ║\n");
    printf("║                Goodbye! 👋               ║\n");
    printf("╚══════════════════════════════════════════╝\n");
    
    Sleep(1000);
    return 0;
}
