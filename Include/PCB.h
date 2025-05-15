#ifndef PCB_H
#define PCB_H

#include <windows.h>

// Process states
#define PROC_STATE_READY    0
#define PROC_STATE_RUNNING  1
#define PROC_STATE_BLOCKED  2

// Queue levels
#define QUEUE_SYSTEM    0    // System processes (highest priority)
#define QUEUE_INTERACTIVE 1  // Interactive processes
#define QUEUE_BATCH     2    // Batch processes
#define QUEUE_BACKGROUND 3   // Background processes (lowest priority)

typedef struct PCB {
    int pid;
    char name[50];
    int base;
    int limit;
    HANDLE processHandle;
    HANDLE threadHandle;
    int is_running;
    int is_minimized;
    int queue_level;        // Which queue the process belongs to
    int time_slice;        // Time slice allocated to the process
    int remaining_time;    // Remaining execution time
    int state;             // Process state (0=ready, 1=running, 2=blocked)
    struct PCB* next;
} PCB;

extern PCB* head;
extern HANDLE pcbMutex;
extern volatile int scheduler_running;

// Process Management Functions
void Create_Process(int pid, const char* name, int base, int limit);
void Remove_Process(int pid);
int Get_Process_Memory(int pid);
int Get_Process_Count(void);
void Display_PCBs(void);
void Minimize_Process(int pid);
void Maximize_Process(int pid);
DWORD WINAPI TaskThread(LPVOID param);
DWORD WINAPI SchedulerThread(LPVOID param);

// Scheduling Functions
void Initialize_Scheduler(void);
void Schedule_Processes(void);
void Set_Process_Queue(int pid, int queue_level);
void Update_Process_State(int pid, int state);
void Multi_Level_Queue_Scheduler(void);
void Aging_Processes(void);

#endif /* PCB_H */