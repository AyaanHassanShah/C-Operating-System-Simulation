// tasks/BrowserLauncher.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int main() {
    char query[256];
    char url[512] = "https://www.google.com/search?q=";

    printf("Enter your search query: ");
    fgets(query, sizeof(query), stdin);

    // Remove newline character from query
    query[strcspn(query, "\n")] = '\0';

    // Replace spaces with '+'
    for (int i = 0; i < strlen(query); i++) {
        if (query[i] == ' ') {
            query[i] = '+';
        }
    }

    strcat(url, query); // Append query to base URL

    // Launch default browser with URL
    ShellExecute(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);

    return 0;
}
