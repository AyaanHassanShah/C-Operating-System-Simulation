#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define MAX_TEXT 1024
#define WPM_WORD_LENGTH 5
#define MIN_ACCURACY 0

void calculateResults(const char* sample, const char* typed, clock_t start, clock_t end) {
    double timeTaken = (double)(end - start) / CLOCKS_PER_SEC;
    
    // Calculate accuracy
    int sampleLen = strlen(sample);
    int typedLen = strlen(typed);
    int correctChars = 0;
    
    for (int i = 0; i < sampleLen && i < typedLen; i++) {
        if (sample[i] == typed[i]) {
            correctChars++;
        }
    }
    
    // Calculate metrics
    double accuracy = (double)correctChars / sampleLen * 100.0;
    
    // WPM = (characters typed / 5) / time in minutes
    // Only count correct characters for WPM
    double wpm = ((double)correctChars / WPM_WORD_LENGTH) / (timeTaken / 60.0);
    
    // Display results with proper formatting
    printf("\n╔═══════════ Results ═══════════╗\n");
    printf("║ Time:     %6.1f seconds     ║\n", timeTaken);
    printf("║ Accuracy: %6.1f%%           ║\n", accuracy);
    printf("║ Speed:    %6.1f WPM        ║\n", wpm);
    printf("╚════════════════════════════════╝\n\n");
}

int main() {
    const char *sampleTexts[] = {
        "The quick brown fox jumps over the lazy dog.",
        "A journey of a thousand miles begins with a single step.",
        "To be or not to be, that is the question.",
        "All that glitters is not gold.",
        "Practice makes perfect."
    };
    
    char typedText[MAX_TEXT];
    int testCount = sizeof(sampleTexts) / sizeof(sampleTexts[0]);
    
    system("cls");
    printf("\n=== Typing Speed Test ===\n\n");
    
    for (int i = 0; i < testCount; i++) {
        printf("Test %d of %d:\n", i + 1, testCount);
        printf("Type this text:\n\n");
        printf("\"%s\"\n\n", sampleTexts[i]);
        printf("Press Enter when ready...");
        getchar();
        
        printf("Start typing now:\n");
        clock_t startTime = clock();
        fgets(typedText, sizeof(typedText), stdin);
        clock_t endTime = clock();
        
        // Remove newline
        typedText[strcspn(typedText, "\n")] = '\0';
        
        calculateResults(sampleTexts[i], typedText, startTime, endTime);
        
        if (i < testCount - 1) {
            printf("Press Enter for next test...");
            getchar();
            system("cls");
        }
    }
    
    printf("Test completed! Press Enter to exit...");
    getchar();
    return 0;
}
