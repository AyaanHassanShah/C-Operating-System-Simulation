#include <stdio.h>
#include <string.h>
#include "../include/PCB.h"

PCB PCB_Table[MAX_TASKS];
int Process_Count = 0;

void Create_Process(int Pid, const char* Name, int Memory_Start, int Memory_Size) 
{
    PCB Process;
    Process.Pid = Pid;
    strcpy(Process.Name, Name);
    Process.Memory_Start = Memory_Start;
    Process.Memory_Size = Memory_Size;
    PCB_Table[Process_Count++] = Process;
}

void Display_PCBs(void) 
{
    printf("\n╔═══════════ Running Tasks ═══════════╗\n");
    for (int i = 0; i < Process_Count; i++) 
    {
        printf("║ PID: %d | Name: %s | Memory: %d KB ║\n",
            PCB_Table[i].Pid,
            PCB_Table[i].Name,
            PCB_Table[i].Memory_Size);
    }
    printf("╚══════════════════════════════════════╝\n");
}
