#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TASKS 100
#define MAX_DESC 256

typedef struct 
{
    char Description[MAX_DESC];
    time_t ReminderTime;
} Task;

Task Tasks[MAX_TASKS];
int TaskCount = 0;

void Add_Task() 
{
    if (TaskCount >= MAX_TASKS) 
    {
        printf("+----------------------------------------+\n");
        printf("|         Task list is full!             |\n");
        printf("+----------------------------------------+\n");
        return;
    }

    printf("+----------------------------------------+\n");
    printf("|        Enter task description:         |\n");
    printf("+----------------------------------------+\n");
    getchar(); // consume leftover newline
    fgets(Tasks[TaskCount].Description, MAX_DESC, stdin);
    Tasks[TaskCount].Description[strcspn(Tasks[TaskCount].Description, "\n")] = '\0';

    int Year, Month, Day, Hour, Minute;
    printf("+----------------------------------------+\n");
    printf("|         Enter reminder time            |\n");
    printf("+----------------------------------------+\n");

    printf("Year (YYYY): ");
    scanf("%d", &Year);
    printf("Month (1-12): ");
    scanf("%d", &Month);
    printf("Day (1-31): ");
    scanf("%d", &Day);
    printf("Hour (0-23): ");
    scanf("%d", &Hour);
    printf("Minute (0-59): ");
    scanf("%d", &Minute);

    if (Year < 2024 || Month < 1 || Month > 12 || Day < 1 || Day > 31 || 
        Hour < 0 || Hour > 23 || Minute < 0 || Minute > 59) 
    {
        printf("+----------------------------------------+\n");
        printf("|         Invalid date/time!             |\n");
        printf("+----------------------------------------+\n");
        return;
    }

    struct tm Time = {0};
    Time.tm_year = Year - 1900;
    Time.tm_mon = Month - 1;
    Time.tm_mday = Day;
    Time.tm_hour = Hour;
    Time.tm_min = Minute;
    Time.tm_sec = 0;

    Tasks[TaskCount].ReminderTime = mktime(&Time);
    TaskCount++;

    printf("+----------------------------------------+\n");
    printf("|         Task added successfully!       |\n");
    printf("+----------------------------------------+\n");
}

void View_Tasks() 
{
    printf("+----------------------------------------+\n");
    if (TaskCount == 0) 
    {
        printf("|          No tasks available.           |\n");
        printf("+----------------------------------------+\n");
        return;
    }

    printf("|              To-Do List                |\n");
    printf("+----------------------------------------+\n");
    for (int i = 0; i < TaskCount; i++) 
    {
        printf("%d. %s\n    Reminder: %s", 
               i + 1, 
               Tasks[i].Description, 
               ctime(&Tasks[i].ReminderTime));
    }
}

void Check_Reminders() 
{
    time_t Now = time(NULL);
    printf("+----------------------------------------+\n");
    printf("|         Checking reminders...          |\n");
    printf("+----------------------------------------+\n");
    for (int i = 0; i < TaskCount; i++) 
    {
        if (difftime(Tasks[i].ReminderTime, Now) <= 0) 
        {
            printf("Reminder: %s\n", Tasks[i].Description);
        }
    }
}

int main() 
{
    int Choice;

    printf("+----------------------------------------+\n");
    printf("|        Welcome to the To-Do List       |\n");
    printf("+----------------------------------------+\n");

    View_Tasks();

    while (1) 
    {
        printf("\n+----------------------------------------+\n");
        printf("|             To-Do List Menu            |\n");
        printf("+----------------------------------------+\n");
        printf("| 1. Add Task                            |\n");
        printf("| 2. View Tasks                          |\n");
        printf("| 3. Check Reminders                     |\n");
        printf("| 4. Exit                                |\n");
        printf("+----------------------------------------+\n");
        printf("Enter your choice: ");
        scanf("%d", &Choice);

        switch (Choice) 
        {
            case 1:
                Add_Task();
                break;
            case 2:
                View_Tasks();
                break;
            case 3:
                Check_Reminders();
                break;
            case 4:
                printf("+----------------------------------------+\n");
                printf("|             Exiting...                 |\n");
                printf("+----------------------------------------+\n");
                exit(0);
            default:
                printf("+----------------------------------------+\n");
                printf("|        Invalid choice. Try again.      |\n");
                printf("+----------------------------------------+\n");
        }
    }

    return 0;
}
