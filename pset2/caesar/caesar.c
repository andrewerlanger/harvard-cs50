#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // Declare variables
    int k;
    int num_chars;
    string text;

    // Check that argc = 2 (i.e. ./caesar + k), kill program if not
    if (argc != 2)
    {
        printf("Correct usage:\n./caesar k\n");
        return 1;
    }

    // Define k
    k = atoi(argv[1]);

    // Prompt user for plaintext
    printf("Plaintext: ");
    text = get_string();

    // Calculate string length, and assign value to num_chars
    num_chars = strlen(text);

    // Begin to print the output
    printf("ciphertext: ");

    // Apply the key to letters only, and print
    for (int i = 0; i < num_chars; i++)
    {
        if (isupper(text[i]))
        {
            printf("%c", (((text[i] + k) - 65) % 26) + 65);
        }
        else if (islower(text[i]))
        {
            printf("%c", (((text[i] + k) - 97) % 26) + 97);
        }
        else
        {
            printf("%c", text[i]);
        }
    }

    // Print the end of the output
    printf("\n");
}