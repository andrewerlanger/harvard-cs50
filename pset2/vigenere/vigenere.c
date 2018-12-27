#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // Declare plaintext, and declare and define keyword k
    string p;
    string k = argv[1];

    // Check that program only took one command-line argument
    if (argc != 2)
    {
        printf("Make sure you only enter one command-line argument\n");
        return 1;
    }

    // Check that keyword is all characters
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Make sure your keyword only contains alphabetical characters\n");
            return 1;
        }
    }

    // Make keyword all lower-case
    for (int m = 0; m < strlen(k); m++)
    {
        if (isupper(k[m]))
        {
            k[m] = tolower(k[m]);
        }
    }

    // Prompt user for plaintext
    printf("plaintext: ");
    p = get_string();

    // Define counter and apply key
    printf("ciphertext: ");
    for (int j = 0, counter = 0; j < strlen(p); j++)
    {
        if (isupper(p[j]))
        {
            p[j] = (((p[j] - 'A') + (k[counter % strlen(k)] - 'a')) % 26) + 'A';
            counter++;
        }
        else if (islower(p[j]))
        {
            p[j] = (((p[j] - 'a') + (k[counter % strlen(k)] - 'a')) % 26) + 'a';
            counter++;
        }
    }

    // Print output
    for (int l = 0; l < strlen(p); l++)
    {
        printf("%c", p[l]);
    }
    printf("\n");

    // That's all folks
    return 0;
}