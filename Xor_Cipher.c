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
    char choice;

    printf("\n======= XOR Cipher Tool =======\n");
    printf("---------------------------------\n\n");

    printf("=> Enter Text to Encrypt: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("=> Enter Encryption Key: ");
    key = getchar();
    while (getchar() != '\n');

    printf("\nProcessing");
    for(int i = 0; i < 3; i++) {
        printf(".");
        Sleep(300);
    }

    xor_encrypt_decrypt(text, key);
    printf("\n\nResult:\n");
    printf("=> Encrypted text: %s\n\n", text);

    printf("Would you like to Decrypt? (y/n): ");
    choice = getchar();

    if (choice == 'y' || choice == 'Y') {
        printf("\nDecrypting");
        for(int i = 0; i < 3; i++) {
            printf(".");
            Sleep(300);
        }
        xor_encrypt_decrypt(text, key);
        printf("\n\nResult:\n");
        printf("=> Decrypted text: %s\n", text);
    }

    printf("\n----------------------\n");
    printf("Operation completed!\n\n");
    return 0;
}
