
#include <stdio.h>
#include <string.h>
#include <time.h>

int main() 
{
    const char *sampleText = "The quick brown fox jumps over the lazy dog.";
    char typedText[1024];
    clock_t startTime, endTime;

    printf("Typing Speed Test\n");
    const char *sampleTexts[] = 
    {
        "The quick brown fox jumps over the lazy dog.",
        "A journey of a thousand miles begins with a single step.",
        "To be or not to be, that is the question."
    };
    int testCount = sizeof(sampleTexts) / sizeof(sampleTexts[0]);

    for (int i = 0; i < testCount; i++) 
    {
        printf("Test %d: Type this: \"%s\"\n", i + 1, sampleTexts[i]);
        printf("Press Enter to start...\n");
        getchar();

        startTime = clock();
        printf("Start typing:\n");
        fgets(typedText, sizeof(typedText), stdin);
        endTime = clock();

        // Simpler way to remove newline
        if (typedText[strlen(typedText) - 1] == '\n') 
        {
            typedText[strlen(typedText) - 1] = '\0';
        }

        double timeTaken = (double)(endTime - startTime) / CLOCKS_PER_SEC;

        int correctChars = 0;
        for (int j = 0; sampleTexts[i][j] && typedText[j]; j++) 
        {
            if (sampleTexts[i][j] == typedText[j]) correctChars++;
        }

        double accuracy = (double)correctChars / strlen(sampleTexts[i]) * 100;
        double wpm = (strlen(typedText) / 5.0) / (timeTaken / 60.0);

        printf("\nResults for Test %d:\n", i + 1);
        printf("Time: %.2f seconds\n", timeTaken);
        printf("Accuracy: %.2f%%\n", accuracy);
        printf("Speed: %.2f WPM\n\n", wpm);
    }
    printf("Press Enter to start...\n");
    getchar();

    startTime = clock();
    printf("Start typing:\n");
    fgets(typedText, sizeof(typedText), stdin);
    endTime = clock();

    // Simpler way to remove newline
    if (typedText[strlen(typedText) - 1] == '\n') 
    {
        typedText[strlen(typedText) - 1] = '\0';
    }

    double timeTaken = (double)(endTime - startTime) / CLOCKS_PER_SEC;

    int correctChars = 0;
    for (int i = 0; sampleText[i] && typedText[i]; i++) 
    {
        if (sampleText[i] == typedText[i]) correctChars++;
    }

    double accuracy = (double)correctChars / strlen(sampleText) * 100;
    double wpm = (strlen(typedText) / 5.0) / (timeTaken / 60.0);

    printf("\nResults:\n");
    printf("Time: %.2f seconds\n", timeTaken);
    printf("Accuracy: %.2f%%\n", accuracy);
    printf("Speed: %.2f WPM\n", wpm);

    return 0;
}
