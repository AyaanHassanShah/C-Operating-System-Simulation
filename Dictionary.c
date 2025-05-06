#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 10000
#define MAX_WORD_LEN 100
#define MAX_DEF_LEN 5000

typedef struct {
    char word[MAX_WORD_LEN];
    char definition[MAX_DEF_LEN];
} DictionaryEntry;

DictionaryEntry dictionary[MAX_WORDS];
int wordCount = 0;

// Convert string to lowercase for comparison
void toLowerStr(char* dest, const char* src) {
    for (int i = 0; src[i]; i++)
        dest[i] = tolower(src[i]);
    dest[strlen(src)] = '\0';
}

// Load cleaned dictionary from cleaned_dictionary.txt
void loadDictionary(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening dictionary file");
        exit(1);
    }

    char line[MAX_DEF_LEN + MAX_WORD_LEN];
    while (fgets(line, sizeof(line), file)) {
        char* token = strstr(line, "::");
        if (token) {
            *token = '\0'; // Split word and definition
            char* word = line;
            char* definition = token + 2;

            strncpy(dictionary[wordCount].word, word, MAX_WORD_LEN - 1);
            strncpy(dictionary[wordCount].definition, definition, MAX_DEF_LEN - 1);
            wordCount++;
        }
    }

    fclose(file);
    printf("Dictionary loaded with %d words.\n", wordCount);
}

// Search for a word and display its definition
void searchWord() {
    char query[MAX_WORD_LEN];
    char lowerQuery[MAX_WORD_LEN];
    printf("\nEnter a word to search: ");
    scanf("%s", query);
    toLowerStr(lowerQuery, query);

    int found = 0;
    for (int i = 0; i < wordCount; i++) {
        char lowerWord[MAX_WORD_LEN];
        toLowerStr(lowerWord, dictionary[i].word);
        if (strcmp(lowerWord, lowerQuery) == 0) {
            printf("\nDefinition for \"%s\":\n%s\n", dictionary[i].word, dictionary[i].definition);
            found = 1;
        }
    }

    if (!found)
        printf("No definition found for \"%s\".\n", query);
}

int main() {
    loadDictionary("cleaned_dictionary.txt");

    while (1) {
        searchWord();
        char choice;
        printf("\nSearch another word? (y/n): ");
        scanf(" %c", &choice);
        if (choice != 'y' && choice != 'Y')
            break;
    }

    printf("Goodbye!\n");
    return 0;
}
