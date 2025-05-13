#include "../Include/PCB.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

PCB* head = NULL;
extern HANDLE pcbMutex;  // Changed to extern since it's declared in Main.c
volatile int scheduler_running = 1;  // Flag to control scheduler thread

// Scheduling constants
#define TIME_SLICE_SYSTEM 50      // 50ms for system processes
#define TIME_SLICE_INTERACTIVE 100 // 100ms for interactive processes
#define TIME_SLICE_BATCH 200      // 200ms for batch processes
#define TIME_SLICE_BACKGROUND 300  // 300ms for background processes
#define AGING_THRESHOLD 5         // Number of time slices before aging

DWORD WINAPI TaskThread(LPVOID param) 
{
    PCB* pcb = (PCB*)param;
    char command[100];
    
    WaitForSingleObject(pcbMutex, INFINITE);
    snprintf(command, sizeof(command), "start cmd /c Bin\\%s.exe", pcb->name);
    pcb->is_running = 1;
    ReleaseMutex(pcbMutex);
    
    system(command);
    
    WaitForSingleObject(pcbMutex, INFINITE);
    pcb->is_running = 0;
    ReleaseMutex(pcbMutex);
    
    return 0;
}

DWORD WINAPI SchedulerThread(LPVOID param) {
    while (scheduler_running) {
        Multi_Level_Queue_Scheduler();
        Aging_Processes();
        Sleep(TIME_SLICE_SYSTEM);  // Use smallest time slice for responsiveness
    }
    return 0;
}

int Get_Process_Memory(int pid) {
    PCB* current = head;
    while (current != NULL) {
        if (current->pid == pid) {
            return current->limit;
        }
        current = current->next;
    }
    return 0;
}

void Remove_Process(int pid) 
{
    PCB* current = head;
    PCB* prev = NULL;

    // Find the process in PCB list
    while (current != NULL && current->pid != pid) 
    {
        prev = current;
        current = current->next;
    }

    // Process not found
    if (current == NULL) 
    {
        printf("\n╔════════ Error ═════════════════╗\n");
        printf("║ Process %d not found!          ║\n", pid);
        printf("╚═══════════════════════════════╝\n");
        return;
    }

    // Find and close the window
    char windowTitle[100];
    snprintf(windowTitle, sizeof(windowTitle), "%s", current->name);
    
    // Find and terminate all windows with matching title
    HWND hwnd = FindWindowA(NULL, windowTitle);
    if (hwnd != NULL) {
        // Try sending WM_CLOSE message first (cleaner)
        SendMessage(hwnd, WM_CLOSE, 0, 0);
        // Give it a moment to close
        Sleep(100);
        // Force terminate if still exists
        if (IsWindow(hwnd)) {
            DestroyWindow(hwnd);
        }
    }
    
    // Terminate the actual process if handle exists
    if (current->processHandle != NULL) 
    {
        TerminateProcess(current->processHandle, 0);
        CloseHandle(current->processHandle);
    }
    
    // Terminate the thread if handle exists
    if (current->threadHandle != NULL) 
    {
        TerminateThread(current->threadHandle, 0);
        CloseHandle(current->threadHandle);
    }

    // Update PCB list links
    if (prev == NULL) 
    {
        // If it's the first node
        head = current->next;
    } 
    else 
    {
        // If it's in middle or end
        prev->next = current->next;
    }

    // Free PCB memory
    free(current);
    
    printf("Process %d terminated and window closed\n", pid);
}

int Get_Process_Count(void) {
    int count = 0;
    PCB* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void Initialize_Scheduler(void) {
    WaitForSingleObject(pcbMutex, INFINITE);
    PCB* current = head;
    while (current != NULL) {
        current->queue_level = QUEUE_INTERACTIVE;  // Default to interactive queue
        current->time_slice = TIME_SLICE_INTERACTIVE;
        current->remaining_time = TIME_SLICE_INTERACTIVE;
        current->state = PROC_STATE_READY;
        current = current->next;
    }
    ReleaseMutex(pcbMutex);
}

void Set_Process_Queue(int pid, int queue_level) {
    WaitForSingleObject(pcbMutex, INFINITE);
    PCB* current = head;
    while (current != NULL) {
        if (current->pid == pid) {
            current->queue_level = queue_level;
            // Set appropriate time slice based on queue
            switch(queue_level) {
                case QUEUE_SYSTEM:
                    current->time_slice = TIME_SLICE_SYSTEM;
                    break;
                case QUEUE_INTERACTIVE:
                    current->time_slice = TIME_SLICE_INTERACTIVE;
                    break;
                case QUEUE_BATCH:
                    current->time_slice = TIME_SLICE_BATCH;
                    break;
                case QUEUE_BACKGROUND:
                    current->time_slice = TIME_SLICE_BACKGROUND;
                    break;
            }
            current->remaining_time = current->time_slice;
            break;
        }
        current = current->next;
    }
    ReleaseMutex(pcbMutex);
}

void Aging_Processes(void) {
    WaitForSingleObject(pcbMutex, INFINITE);
    PCB* current = head;
    while (current != NULL) {
        if (current->state == PROC_STATE_READY) {
            // If process has been waiting too long, promote it
            if (current->queue_level > QUEUE_SYSTEM) {
                current->queue_level--;
                // Update time slice for new queue
                switch(current->queue_level) {
                    case QUEUE_SYSTEM:
                        current->time_slice = TIME_SLICE_SYSTEM;
                        break;
                    case QUEUE_INTERACTIVE:
                        current->time_slice = TIME_SLICE_INTERACTIVE;
                        break;
                    case QUEUE_BATCH:
                        current->time_slice = TIME_SLICE_BATCH;
                        break;
                }
                current->remaining_time = current->time_slice;
            }
        }
        current = current->next;
    }
    ReleaseMutex(pcbMutex);
}

void Multi_Level_Queue_Scheduler(void) {
    WaitForSingleObject(pcbMutex, INFINITE);
    
    // First, check if there's a running process
    PCB* current = head;
    int found_running = 0;
    
    while (current != NULL) {
        if (current->state == PROC_STATE_RUNNING) {
            found_running = 1;
            current->remaining_time -= TIME_SLICE_SYSTEM;
            
            if (current->remaining_time <= 0) {
                // Time slice expired
                current->state = PROC_STATE_READY;
                current->remaining_time = current->time_slice;
            }
            break;
        }
        current = current->next;
    }
    
    // If no running process or current process expired, find next process to run
    if (!found_running || current->remaining_time <= 0) {
        // Search queues in priority order
        for (int queue = QUEUE_SYSTEM; queue <= QUEUE_BACKGROUND; queue++) {
            current = head;
            while (current != NULL) {
                if (current->state == PROC_STATE_READY && current->queue_level == queue) {
                    current->state = PROC_STATE_RUNNING;
                    current->remaining_time = current->time_slice;
                    found_running = 1;
                    break;
                }
                current = current->next;
            }
            if (found_running) break;
        }
    }
    
    ReleaseMutex(pcbMutex);
}

void Update_Process_State(int pid, int state) {
    WaitForSingleObject(pcbMutex, INFINITE);
    PCB* current = head;
    while (current != NULL) {
        if (current->pid == pid) {
            current->state = state;
            break;
        }
        current = current->next;
    }
    ReleaseMutex(pcbMutex);
}

void Round_Robin_Scheduler(void) {
    WaitForSingleObject(pcbMutex, INFINITE);
    PCB* current = head;
    int found_running = 0;
    
    // First, find if there's a running process
    while (current != NULL) {
        if (current->state == PROC_STATE_RUNNING) {
            found_running = 1;
            current->remaining_time -= TIME_SLICE_SYSTEM;
            
            if (current->remaining_time <= 0) {
                // Time slice expired, move to next process
                current->state = PROC_STATE_READY;
                current->remaining_time = TIME_SLICE_SYSTEM;
                
                // Find next ready process
                PCB* next = current->next;
                while (next != NULL) {
                    if (next->state == PROC_STATE_READY) {
                        next->state = PROC_STATE_RUNNING;
                        break;
                    }
                    next = next->next;
                }
                if (next == NULL) {
                    // If no next process found, start from beginning
                    next = head;
                    while (next != current) {
                        if (next->state == PROC_STATE_READY) {
                            next->state = PROC_STATE_RUNNING;
                            break;
                        }
                        next = next->next;
                    }
                }
            }
            break;
        }
        current = current->next;
    }
    
    // If no running process found, start the first ready process
    if (!found_running) {
        current = head;
        while (current != NULL) {
            if (current->state == PROC_STATE_READY) {
                current->state = PROC_STATE_RUNNING;
                current->remaining_time = TIME_SLICE_SYSTEM;
                break;
            }
            current = current->next;
        }
    }
    
    ReleaseMutex(pcbMutex);
}

// Update Create_Process to initialize queue level
void Create_Process(int pid, const char* name, int base, int limit) 
{
    PCB* newPCB = (PCB*)malloc(sizeof(PCB));
    newPCB->pid = pid;
    strncpy(newPCB->name, name, 49);
    newPCB->name[49] = '\0';
    newPCB->base = base;
    newPCB->limit = limit;
    newPCB->is_running = 0;
    newPCB->is_minimized = 0;
    newPCB->processHandle = NULL;
    newPCB->queue_level = QUEUE_INTERACTIVE;  // Default to interactive queue
    newPCB->time_slice = TIME_SLICE_INTERACTIVE;
    newPCB->remaining_time = TIME_SLICE_INTERACTIVE;
    newPCB->state = PROC_STATE_READY;
    newPCB->next = NULL;
    
    // Create thread for the task
    newPCB->threadHandle = CreateThread(NULL, 0, TaskThread, newPCB, 0, NULL);
    
    WaitForSingleObject(pcbMutex, INFINITE);
    if (head == NULL) {
        head = newPCB;
    } else {
        PCB* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newPCB;
    }
    ReleaseMutex(pcbMutex);
}

void Minimize_Process(int pid) 
{
    WaitForSingleObject(pcbMutex, INFINITE);
    PCB* current = head;
    while (current != NULL) {
        if (current->pid == pid) {
            current->is_minimized = 1;
            // Find window by title and minimize it
            HWND hwnd = FindWindowA(NULL, current->name);
            if (hwnd != NULL) {
                ShowWindow(hwnd, SW_MINIMIZE);
            }
            printf("Process %d minimized\n", pid);
            break;
        }
        current = current->next;
    }
    ReleaseMutex(pcbMutex);
}

void Maximize_Process(int pid) 
{
    WaitForSingleObject(pcbMutex, INFINITE);
    PCB* current = head;
    while (current != NULL) {
        if (current->pid == pid) {
            current->is_minimized = 0;
            // Find window by title and maximize it
            HWND hwnd = FindWindowA(NULL, current->name);
            if (hwnd != NULL) {
                ShowWindow(hwnd, SW_MAXIMIZE);
            }
            printf("Process %d maximized\n", pid);
            break;
        }
        current = current->next;
    }
    ReleaseMutex(pcbMutex);
}

// Update Display_PCBs to show queue information
void Display_PCBs(void) 
{
    WaitForSingleObject(pcbMutex, INFINITE);
    PCB* current = head;
    
    printf("\n╔═══════════ Running Processes ════════════╗\n");
    if (current == NULL) {
        printf("║ No processes running                     ║\n");
    } else {
        printf("║ PID | Name           | Status  | Queue   ║\n");
        printf("║-------------------------------------     ║\n");
        while (current != NULL) {
            const char* state_str;
            switch(current->state) {
                case PROC_STATE_READY:
                    state_str = "Ready  ";
                    break;
                case PROC_STATE_RUNNING:
                    state_str = "Running";
                    break;
                case PROC_STATE_BLOCKED:
                    state_str = "Blocked";
                    break;
                default:
                    state_str = "Unknown";
            }
            
            const char* queue_str;
            switch(current->queue_level) {
                case QUEUE_SYSTEM:
                    queue_str = "System ";
                    break;
                case QUEUE_INTERACTIVE:
                    queue_str = "Inter  ";
                    break;
                case QUEUE_BATCH:
                    queue_str = "Batch  ";
                    break;
                case QUEUE_BACKGROUND:
                    queue_str = "Back   ";
                    break;
                default:
                    queue_str = "Unknown";
            }
            
            printf("║ %3d | %-14s | %s | %s ║\n", 
                   current->pid, 
                   current->name,
                   state_str,
                   queue_str);
            current = current->next;
        }
    }
    printf("╚══════════════════════════════════════════╝\n");
    ReleaseMutex(pcbMutex);
}