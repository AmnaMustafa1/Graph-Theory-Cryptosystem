#include "./Encrypt/encrypt.h"      // Includes the custom header for encryption functions and structures
#include "./Decrypt/decrypt.h"      // Includes the custom header for decryption functions and structures
#include <stdio.h>                  // For standard input/output functions (like printf, scanf)
#include <stdlib.h>                 // For memory functions like malloc() and free()

int main() {
    char text[100];                // Declare a character array to store user input (up to 99 characters + null terminator)
    
    printf("Text a message: ");    // Ask the user to input a message
    scanf("%99s", text);           // Read input (a word, without spaces) safely into the text array

    Message msg;                   // Declare a variable to hold the encrypted message structure
    keyList kList = NULL;          // Initialize the key list pointer to NULL (will be filled during encryption)

    msg = encrypt(text, &kList);   // Encrypt the user’s text, and store keys in kList

    char *decryptedText = decrypt(msg, kList);  // Decrypt the message using the stored key list

    graphList g = msg.gList;       // Pointer to the graph list from the encrypted message
    keyList k = kList;             // Copy the key list pointer for iteration

    printf("\nEncryption result:\n");  // Display header for encryption output

    int i = 0;                      // Index to keep track of the character position
    while (g != NULL && k != NULL) {      // Loop while there are still graphs and keys to process
        printf("\nchar: %c\n", decryptedText[i]);       // Print the corresponding decrypted character
        printf("key: {%d %d}\n", k->info.first, k->info.last);  // Show the encryption key used (start and end node of path)
        displayGraph(g->graf);      // Call a function to visually display the graph used for encryption
        g = g->next;                // Move to the next graph in the list
        k = k->next;                // Move to the next key in the list
        i++;                        // Move to the next character
    }

    decryptedText[msg.len] = '\0'; // Null-terminate the decrypted text (just in case)

    printf("\nThe decrypted Text: %s\n", decryptedText);  // Print the final decrypted message

    free(decryptedText);           // Free the dynamically allocated memory for decrypted text

    return 0;                      // End the program
}

