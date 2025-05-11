#include <stdio.h>
#include <stdlib.h>
#include <windows.h>  // Required for Sleep()

int main() 
{
    // Using system() to list files in the current directory
    system("dir");

    // Delay for 10 seconds (10000 milliseconds)
    Sleep(10000);
    return 0;
}
