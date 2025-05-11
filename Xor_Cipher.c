#include <stdio.h>
#include <string.h>
#include <windows.h>

void xor_encrypt_decrypt(char* text, char key) {
    for (int i = 0; text[i] != '\0'; i++) {
        text[i] = text[i] ^ key;  // XOR operation with the key
    }
}

int main() {
    char text[100];
    char key;
    char guess;
    int attempts = 3;
    int correct = 0;

    printf("\n+------- XOR Cipher Guessing Game -------+\n");
    Sleep(300);
    printf("|                                        |\n");

    Sleep(300);
    printf("| Enter Text to Encrypt:                 |\n");
    Sleep(300);
    printf("| ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    Sleep(300);
    printf("| Enter Encryption Key:                  |\n");
    Sleep(300);
    printf("| ");
    key = getchar();
    while (getchar() != '\n');

    Sleep(300);
    printf("|                                        |\n");
    printf("| Encrypting");
    for(int i = 0; i < 3; i++) {
        printf(".");
        Sleep(500);
    }

    xor_encrypt_decrypt(text, key);
    Sleep(300);
    printf("\n|                                        |\n");
    Sleep(300);
    printf("| Encrypted text: %s\n", text);
    Sleep(300);
    printf("|                                        |\n");

    Sleep(300);
    printf("| Now try to guess the key to decrypt!   |\n");
    Sleep(300);
    printf("| You have 3 attempts.                   |\n");
    Sleep(300);
    printf("|                                        |\n");

    while (attempts > 0 && !correct) {
        Sleep(300);
        printf("| Attempts remaining: %d                  |\n", attempts);
        Sleep(300);
        printf("| Enter your guess: ");
        guess = getchar();
        while (getchar() != '\n');

        if (guess == key) {
            correct = 1;
            Sleep(300);
            printf("|                                        |\n");
            Sleep(300);
            printf("| Correct guess! Decrypting message...   |\n");
            Sleep(10000);
            xor_encrypt_decrypt(text, key);
            printf("| Decrypted text: %s\n", text);
        } else {
            attempts--;
            Sleep(500);
            printf("| Wrong guess! Try again.               |\n");
        }
        Sleep(300);
        printf("|                                        |\n");
    }

    if (!correct) {
        Sleep(10000);
        printf("| Game Over! You couldn't guess the key.   |\n");
        Sleep(300);
        printf("| The message remains encrypted.           |\n");
    }

    Sleep(10000);
    printf("|                                        |\n");
    printf("+----------------------------------------+\n");
    return 0;
}
