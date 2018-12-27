#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

//define node
typedef struct node
{
    char name[20];
    char hash[15];
    struct node* next;
}
node;

//crack_it function
void crack_it(char* salt, char* guess, node* n);

int main(void)
{
    //declare variables
    char name_buffer[20];
    char hash_buffer[15];
    bool first_node = true;
    node* head;
    node* tail;
    node* trav;
    node* temp;
    node* new_node;

    //welcome user to program
    printf("\nWELCOME TO CODE CRACKER\n\n"
    "enter your hashes, or hit '$' to get cracking\n\n");

    //prompt user for names + hashes
    while (true)
    {
        //commit name to buffer
        printf("name: ");
        fgets(name_buffer, sizeof(name_buffer)/sizeof(char), stdin);

        //check for exit
        if (strncmp(name_buffer, "$\n", 2) == 0)
        {
            break;
        }

        //remove line-break
        int len1 = strlen(name_buffer);
        for (int i = 0; i < len1; i ++)
        {
            if (name_buffer[i] == '\n')
            {
                name_buffer[i] = '\0';
            }
        }

        //commit hash to buffer
        printf("hash: ");
        fgets(hash_buffer, sizeof(hash_buffer)/sizeof(char), stdin);
        printf("\n");

        //remove line-break
        int len2 = strlen(hash_buffer);
        for (int i = 0; i < len2; i ++)
        {
            if (hash_buffer[i] == '\n')
            {
                hash_buffer[i] = '\0';
            }
        }


        //create new node
        new_node = malloc(sizeof(node));
        if (!new_node)
        {
            printf("error creating new node\n");
            return 1;
        }

        //commit name + hash to node
        strcpy(new_node->name, name_buffer);
        strcpy(new_node->hash, hash_buffer);

        //point head to new node
        if (first_node == true)
        {
            head = new_node;
            tail = new_node;
            first_node = false;
        }

        //update pointers
        new_node->next = NULL;
        tail->next = new_node;
        tail = new_node;
    }

    //print all names + hashes
    trav = head;
    int counter = 1;
    while (trav)
    {
        printf("STUDENT %d\nname: %s\nhash: %s\n\n", counter, trav->name, trav->hash);
        counter++;
        trav = trav->next;
    }

    //update user
    printf("\ntesting all 4-digit passcodes, please wait...\n\n");

    //declare variables
    char guess[6] = {'\0'};
    char salt[3] = {'5', '0', '\0'};
    char* alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int length = strlen(alphabet);

    //test all possibe 4-digit passcodes
    for (int p3 = 0; p3 < length; p3++)
    {
        for (int p2 = 0; p2 < length; p2++)
        {
            for (int p1 = 0; p1 < length; p1++)
            {
                for (int p0 = 0; p0 < length; p0++)
                {
                    //1-digit guesses
                    guess[0] = alphabet[p0];
                    crack_it(salt, guess, head);
                }
                //2-digit guesses
                guess[1] = alphabet[p1];
                crack_it(salt, guess, head);
            }
            //3-digit guesses
            guess[2] = alphabet[p2];
            crack_it(salt, guess, head);
        }
        //4-digit guesses
        guess[3] = alphabet[p3];
        crack_it(salt, guess, head);
    }

    //free memory
    trav = head;
    while (trav != NULL)
    {
        temp = trav->next;
        free(trav);
        trav = temp;
    }

    //that's all folks
    return 0;
}

void crack_it(char* salt, char* guess, node* n)
{
    //search through linked list
    while (n != NULL)
    {
        if (strcmp(crypt(guess, salt), n->hash) == 0)
        {
            printf("SUCCESS\n");
            printf("%s's passcode is %s\n\n", n->name, guess);
            break;
        }
        n = n->next;
    }

}