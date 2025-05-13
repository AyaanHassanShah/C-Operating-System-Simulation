#include <stdio.h>
#include <stdlib.h>
#include <windows.h>  // Required for Sleep()

int main()
{
    // Using system() to list running processes on Windows
    system("tasklist");
     Sleep(10000);
    return 0;
}
