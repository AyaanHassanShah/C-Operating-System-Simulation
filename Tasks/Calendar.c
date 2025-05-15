#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <conio.h>    // Add this header for _kbhit and _getch

void printCalendar(int month, int year) 
{
    char *months[] = {
        "January", "February", "March", "April",
        "May", "June", "July", "August",
        "September", "October", "November", "December"
    };
    
    int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        days[1] = 29;
        

        struct tm firstDay = {0};
    firstDay.tm_year = year - 1900;
    firstDay.tm_mon = month - 1;
    firstDay.tm_mday = 1;
    mktime(&firstDay);
    
    printf("\n+---------- %s %d ----------+\n", months[month-1], year);
    printf("| Sun Mon Tue Wed Thu Fri Sat |\n");
    printf("|");
    
    // Print leading spaces
    for(int i = 0; i < firstDay.tm_wday; i++)
        printf("    ");
    
    // Print days
    for(int i = 1; i <= days[month-1]; i++) 
    {
        printf("%3d ", i);
        if((i + firstDay.tm_wday) % 7 == 0 && i != days[month-1])
            printf(" |\n|");
    }
    
    // Print trailing spaces
    int lastDay = (days[month-1] + firstDay.tm_wday) % 7;
    if(lastDay != 0)
        for(int i = 0; i < (7 - lastDay); i++)
            printf("    ");
            
    printf(" |\n+----------------------------------+\n");
}

int main() 
{
    // Get current time
    time_t now = time(NULL);
    struct tm *currentTime = localtime(&now);
    
    int currentMonth = currentTime->tm_mon + 1;
    int currentYear = currentTime->tm_year + 1900;
    
    system("cls");
    printf("\nSystem Calendar\n");
    
    // Print current month
    printCalendar(currentMonth, currentYear);
    
    // Allow viewing next/previous months
    printf("\nControls:\n");
    printf("N - Next Month\n");
    printf("P - Previous Month\n");
    printf("ESC - Exit\n");
    
    while(1) 
    {
        if(_kbhit()) 
        {
            char key = _getch();
            switch(key) 
            {
                case 'n':
                case 'N':
                    currentMonth++;
                    if(currentMonth > 12) 
                    {
                        currentMonth = 1;
                        currentYear++;
                    }
                    system("cls");
                    printCalendar(currentMonth, currentYear);
                    break;
                    
                case 'p':
                case 'P':
                    currentMonth--;
                    if(currentMonth < 1) 
                    {
                        currentMonth = 12;
                        currentYear--;
                    }
                    system("cls");
                    printCalendar(currentMonth, currentYear);
                    break;
                    
                case 27: // ESC
                    return 0;
            }
            printf("\nControls: N-Next Month, P-Previous Month, ESC-Exit\n");
        }
    }
    
    return 0;
}