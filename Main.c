#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "../include/PCB.h"

// Global Variables
int Total_Ram;
int Total_HDD;
int CPU_Cores;
int Available_RAM;
int pid = 0;

void launch_task(const char* task_name, int mem_size) 
{
    if (mem_size <= Available_RAM) 
    {
        printf("\n╔═══════════ Launching Task ═══════════╗\n");
        printf("║  Starting: %-20s      ║\n", task_name);
        printf("║  Memory allocated: %-6d KB         ║\n", mem_size);
        
        char command[100];
        snprintf(command, sizeof(command), "Bin\\%s.exe", task_name);
        Create_Process(pid++, task_name, Available_RAM, mem_size);
        Available_RAM -= mem_size;
        system(command);
        
        printf("╚══════════════════════════════════════╝\n");
    } 
    else 
    {
        printf("\n╔══════════════ Error ══════════════╗\n");
        printf("║   Insufficient memory available!   ║\n");
        printf("║   Available RAM: %-6d KB        ║\n", Available_RAM);
        printf("╚══════════════════════════════════════╝\n");
    }
}

void show_task_menu() 
{
    int choice, mem;
    while (1) 
    {
        printf("\n╔═══════════ Available Tasks ════════════╗\n");
        printf("║  1. Calculator                         ║\n");
        printf("║  2. Alarm Clock                        ║\n");
        printf("║  3. Countdown Timer                    ║\n");
        printf("║  4. Mini File Explorer                 ║\n");
        printf("║  5. Notepad                            ║\n");
        printf("║  6. Simple Task Manager                ║\n");
        printf("║  7. Temperature Converter              ║\n");
        printf("║  8. Tic Tac Toe                        ║\n");
        printf("║  9. To-Do List                         ║\n");
        printf("║ 10. Typing Speed Test                  ║\n");
        printf("║ 11. Show Running Tasks                 ║\n");
        printf("║  0. Exit to Main Menu                  ║\n");
        printf("╚════════════════════════════════════════╝\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if (choice == 0) break;
        if (choice == 11) 
        {
            Display_PCBs();
            continue;
        }

        printf("Enter memory size in KB: ");
        scanf("%d", &mem);

        switch (choice) 
        {
            case 1: launch_task("Calculator", mem); break;
            case 2: launch_task("AlarmClock", mem); break;
            case 3: launch_task("CountdownTimer", mem); break;
            case 4: launch_task("MiniFileExplorer", mem); break;
            case 5: launch_task("Notepad", mem); break;
            case 6: launch_task("SimpleTaskManager", mem); break;
            case 7: launch_task("TemperatureConverter", mem); break;
            case 8: launch_task("TicTacToe", mem); break;
            case 9: launch_task("TodoList", mem); break;
            case 10: launch_task("TypingSpeed", mem); break;
            default: printf("Invalid choice!\n");
        }
    }
}

void Boot_Seqence() {
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
    printf("\n╔══════════════════════════════════════════╗\n");
    printf("║           System Ready to Use!           ║\n");
    printf("╚══════════════════════════════════════════╝\n");
}

void Input_Specs() {
    printf("\n╔═══════ Enter System Specifications ═══════╗\n");
    printf("║                                           ║\n");
    printf("    Enter total RAM (in GB): ");
    scanf("%d", &Total_Ram);
    printf("    Enter total HDD (in GB): ");
    scanf("%d", &Total_HDD);
    printf("    Enter number of CPU cores: ");
    scanf("%d", &CPU_Cores);
    printf("║                                           ║\n");
    printf("╚═══════════════════════════════════════════╝\n");
}

void Display_Welcome() {
    // printf("\n╔══════════════════════════════════════╗\n");
    // printf("║         System Information           ║\n");
    // printf("║      By Syed Ayaan Hassan Shah       ║\n");
    // printf("╚══════════════════════════════════════╝\n\n");

    printf("╔══════════ System Specifications ═════════╗\n");
    printf("║                                          ║\n");
    printf("║    Memory (RAM)  : %6d Gigabytes      ║\n", Total_Ram);
    printf("║    Storage (HDD) : %6d Gigabytes      ║\n", Total_HDD);
    printf("║    CPU Cores     : %6d Cores          ║\n", CPU_Cores);
    printf("║                                          ║\n");
    printf("╚══════════════════════════════════════════╝\n");

    printf("\n╔══════════════════════════════════════╗\n");
    printf("║         Developed with ❤ by          ║\n");
    printf("║      Syed Ayaan Hassan Shah          ║\n");
    printf("╚══════════════════════════════════════╝\n");
}

int main() {
    system("chcp 65001"); // Set console to UTF-8
    system("cls");        // Clear screen
    
    printf("\n╔══════════════════════════════════════════╗\n");
    printf("║              Welcome to MyOS             ║\n");
    printf("╚══════════════════════════════════════════╝\n");
    
    Boot_Seqence();
    Input_Specs();
    Display_Welcome();
    
    // Initialize available RAM
    Available_RAM = Total_Ram * 1024 * 1024; // Convert GB to KB
    
    show_task_menu();
    
    printf("\n╔══════════════════════════════════════════╗\n");
    printf("║         Shutting down MyOS...            ║\n");
    printf("║              Goodbye! 👋                 ║\n");
    printf("╚══════════════════════════════════════════╝\n");
    
    Sleep(1000); // Pause for 1 second before exit
    return 0;
}