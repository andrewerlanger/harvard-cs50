#define _XOPEN_SOURCE
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    // Check for a single command-line argument
    if (argc != 2)
    {
        printf("Just the one command-line argument, thanks\n");
        return 1;
    }

    // Initialize key variables
    char *hash = argv[1];
    char salt[3] = {'\0'};
    strncpy(salt, hash, 2);
    char guess[6] = {'\0'};
    char *alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int length = strlen(alphabet);

    // Generate guesses
    for (int a4 = 0; a4 < length; a4++)
    {
        for (int a3 = 0; a3 < length; a3++)
        {
            for (int a2 = 0; a2 < length; a2++)
            {
                for (int a1 = 0; a1 < length; a1++)
                {
                    for (int a0 = 0; a0 < length; a0++)
                    {
                        guess[0] = alphabet[a0];
                        if (strcmp(crypt(guess, salt), hash) == 0)
                        {
                            printf("you cracked it!\npassword is \"%s\"\n", guess);
                            return 0;
                        }
                    }
                    guess[1] = alphabet[a1];
                    if (strcmp(crypt(guess, salt), hash) == 0)
                    {
                        printf("you cracked it!\npassword is \"%s\"\n", guess);
                        return 0;
                    }
                }
                guess[2] = alphabet[a2];
                if (strcmp(crypt(guess, salt), hash) == 0)
                {
                    printf("you cracked it!\npassword is \"%s\"\n", guess);
                    return 0;
                }
            }
            guess[3] = alphabet[a3];
            if (strcmp(crypt(guess, salt), hash) == 0)
            {
                printf("you cracked it!\npassword is \"%s\"\n", guess);
                return 0;
            }
        }
        guess[4] = alphabet[a4];
        printf("still working on it...\n");
        if (strcmp(crypt(guess, salt), hash) == 0)
        {
            printf("you cracked it!\npassword is \"%s\"\n", guess);
            return 0;
        }
    }

    // Alert user if password not found
    printf("Couldn't find anything\n");

    // That's all folks
    return 0;
}