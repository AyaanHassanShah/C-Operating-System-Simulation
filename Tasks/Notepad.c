#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTENT_SIZE 1024

void writeToFile(const char *filename, const char *content) 
{
    FILE *file = fopen(filename, "a"); // Open file in append mode
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s\n", content);
    fclose(file);
}

void readFromFile(const char *filename) 
{
    FILE *file = fopen(filename, "r+"); // Open file in read and write mode
    if (file == NULL) {
        printf("File does not exist. It will be created when you write content.\n");
        return;
    }
    char buffer[MAX_CONTENT_SIZE];
    printf("Current content of the file:\n");
    while (fgets(buffer, MAX_CONTENT_SIZE, file) != NULL) 
    {
        printf("%s", buffer);
    }
    fclose(file);
}

int main() 
{
    char filename[256];
    char content[MAX_CONTENT_SIZE];
    int choice;

    printf("Enter the filename: ");
    scanf("%255s", filename);

    while (1) {
        printf("\n1. Write to file\n2. Read from file\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character left by scanf

        switch (choice)
         {
            case 1:
                printf("Enter content to write (end with a newline):\n");
                fgets(content, MAX_CONTENT_SIZE, stdin);
                content[strcspn(content, "\n")] = '\0'; // Remove trailing newline
                writeToFile(filename, content);
                break;
            case 2:
                readFromFile(filename);
                break;
            case 3:
                printf("Exiting Notepad.\n");
                exit(EXIT_SUCCESS);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}