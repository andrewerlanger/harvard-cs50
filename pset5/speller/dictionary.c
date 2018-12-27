// Implements a dictionary's functionality

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

#define ALPHABET 27

// Typedef trie node
typedef struct node
{
    bool is_word;
    struct node *children[ALPHABET];
}
node;

// Initialize global variables
node *root = NULL;
bool is_loaded = false;
int total_words = 0;

// Frees memory from trie structure
void freemem(node *free_node)
{
    for (int a = 0; a < ALPHABET; a++)
    {
        if (free_node->children[a] != NULL)
        {
            freemem(free_node->children[a]);
        }
    }
    free(free_node);
    return;
}

// Creates new node
node *create(void)
{
    node *create_node = malloc(sizeof(node));
    if (!create_node)
    {
        fprintf(stderr, "error creating new node\n");
        return NULL;
    }

    for (int n = 0; n < ALPHABET; n++)
    {
        create_node->children[n] = NULL;
    }
    create_node->is_word = NULL;
    return create_node;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Calculate length + declare variables
    int length = strlen(word), j, child;
    node *trav = root;

    // Initialize loop
    for (j = 0; j < length; j++)
    {
        // Calculate child value
        if (word[j] == '\'')
        {
            child = ALPHABET - 1;
        }
        else if (isupper(word[j]))
        {
            child = word[j] - 65;
        }
        else
        {
            child = word[j] - 97;
        }

        // Check for NULL at that child
        if (trav->children[child] == NULL)
        {
            return false;
        }
        else
        {
            trav = trav->children[child];
        }
    }
    // Return true if is_word is true, else return false
    if (trav->is_word == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    root = create();

    // Open file
    FILE *input_pointer = fopen(dictionary, "r");
    if (!input_pointer)
    {
        fprintf(stderr, "open file error\n");
        unload();
        return false;
    }

    // Declare variables
    char word[LENGTH + 1];
    int child, length, i;
    node *trav = NULL;
    node *letter = NULL;

    // Read words from dictionary + commit to memory
    while (fscanf(input_pointer, "%s", word) != EOF)
    {
        // Calculate word length + initialize trav
        total_words++;
        length = strlen(word);
        trav = root;

        // Commit word to trie structure, one letter at a time
        for (i = 0; i < length; i++)
        {
            // Calculate child number
            if (word[i] == '\'')
            {
                child = ALPHABET - 1;
            }
            else
            {
                child = word[i] - 97;
            }

            // Adjust pointers: case of existing node
            if (trav->children[child])
            {
                trav = trav->children[child];
            }
            // Adjust pointers: case of new node
            else
            {
                letter = create();
                trav->children[child] = letter;
                trav = letter;
            }
        }
        trav->is_word = true;
    }

    // Close dictionary
    fclose(input_pointer);
    is_loaded = true;
    return true;
}


// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{

    // Return 0 if dictionary not loaded, else return total_words
    if (is_loaded == false)
    {
        return 0;
    }
    else
    {
        return total_words;
    }

}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Check dictionary is loaded
    if (is_loaded == false)
    {
        fprintf(stderr, "dictionary does not seem to be loaded\n");
        return false;
    }

    // Free memory
    freemem(root);
    is_loaded = false;
    return true;
}

