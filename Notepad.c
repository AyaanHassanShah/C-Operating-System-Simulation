#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTENT_SIZE 1024

void writeToFile(const char *filename, const char *content) 
{
    FILE *file = fopen(filename, "a"); // Append mode
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s\n", content);
    fclose(file);
    printf("\n╔═════════════════════════════════════════════╗\n");
    printf(  "║        ✅ Content written successfully!     ║\n");
    printf(  "╚═════════════════════════════════════════════╝\n");
}

void readFromFile(const char *filename) 
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("\n╔═════════════════════════════════════════════╗\n");
        printf(  "║  ⚠️  File does not exist. Will be created.   ║\n");
        printf(  "╚═════════════════════════════════════════════╝\n");
        return;
    }

    char buffer[MAX_CONTENT_SIZE];
    printf("\n╔══════════════ File Content ═════════════════╗\n");
    while (fgets(buffer, MAX_CONTENT_SIZE, file) != NULL) 
    {
        printf("║ %-43s ║\n", buffer[strcspn(buffer, "\n")] == '\0' ? buffer : strtok(buffer, "\n"));
    }
    printf("╚═════════════════════════════════════════════╝\n");
    fclose(file);
}

void showMenu() {

    printf("\n╔════════════════════ Notepad ═══════════════════╗\n");
    printf("║  1. Write to file                              ║\n");
    printf("║  2. Read from file                             ║\n");
    printf("║  3. Exit                                       ║\n");
    printf("╚════════════════════════════════════════════════╝\n");
    printf("Enter your choice: ");
}

int main() 
{
    char filename[256];
    char content[MAX_CONTENT_SIZE];
    int choice;

    printf("╔═════════════════════════════════════════════╗\n");
    printf("║            📝 Welcome to Notepad            ║\n");
    printf("╚═════════════════════════════════════════════╝\n");

    printf("\nEnter the filename: ");
    scanf("%255s", filename);
    getchar(); // Clear newline from buffer

    while (1) {
        showMenu();
        scanf("%d", &choice);
        getchar(); // Consume leftover newline

        switch (choice) {
            case 1:
                printf("Enter content to write:\n");
                fgets(content, MAX_CONTENT_SIZE, stdin);
                content[strcspn(content, "\n")] = '\0'; // Remove newline
                writeToFile(filename, content);
                break;
            case 2:
                readFromFile(filename);
                break;
            case 3:
                printf("\n╔═════════════════════════════════════════════╗\n");
                printf(  "║       👋 Exiting Notepad. Goodbye!          ║\n");
                printf(  "╚═════════════════════════════════════════════╝\n");
                exit(EXIT_SUCCESS);
            default:
                printf("\n❌ Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
