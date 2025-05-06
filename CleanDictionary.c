#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 1024
#define MAX_WORD_LEN 100
#define MAX_DEF_LEN 5000

// Check if a line starts with a new dictionary word
int isNewWordLine(const char *line) {
    return isalpha(line[0]) && strchr(line, '.');
}

int main() {
    FILE *in = fopen("Old_Dictionary.txt", "r");
    FILE *out = fopen("Cleaned_Dictionary.txt", "w");

    if (!in || !out) {
        perror("File open error");
        return 1;
    }

    char line[MAX_LINE];
    char currentWord[MAX_WORD_LEN] = "";
    char currentDef[MAX_DEF_LEN] = "";
    int started = 0;

    while (fgets(line, sizeof(line), in)) {
        if (isNewWordLine(line)) {
            if (started) {
                fprintf(out, "%s::%s\n", currentWord, currentDef);
            }

            // Reset and start a new word
            sscanf(line, "%s", currentWord);
            strcpy(currentDef, line);
            started = 1;
        } else if (started) {
            strcat(currentDef, line);
        }
    }

    if (started) {
        fprintf(out, "%s::%s\n", currentWord, currentDef);
    }

    fclose(in);
    fclose(out);
    printf("Dictionary cleaned and saved to cleaned_dictionary.txt\n");
    return 0;
}
