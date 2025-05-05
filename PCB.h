#ifndef PCB_H
#define PCB_H

#define MAX_TASKS 20

typedef struct 
{
    int Pid;
    char Name[30];
    int Memory_Start;
    int Memory_Size;
} PCB;

void Create_Process(int Pid, const char* Name, int Memory_Start, int Memory_Size);
void Display_PCBs(void);

#endif

