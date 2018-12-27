#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

// Typedef BYTE
typedef uint8_t BYTE;

// 512 byte data structure
typedef struct
{
    BYTE opening[4];
    BYTE closing[508];
} __attribute__((__packed__))
RECSTRUCT;

int EndsWith(char *string, char *suffix);
y
int main(int argc, char *argv[])
{
    // Initialize rec + counter
    char name[10] = {'\0'};
    int counter = 0;
    FILE *input_pointer = NULL;
    FILE *output_pointer = NULL;
    RECSTRUCT rec;

    // Check for correct number of command-line arguments (i.e. 2)
    if (argc != 2)
    {
        fprintf(stderr, "Correct usage: ./recover file.raw\n");
        return 1;
    }

    // Capture input file as string
    char *input_file = argv[1];

    // Check input file has correct file extension (.raw)
    if (EndsWith(input_file, ".raw") != 0)
    {
        fprintf(stderr, "Oops, seems %s isn't a .raw file\n", input_file);
        return 1;
    }

    // Open input file + NULL check
    input_pointer = fopen(input_file, "r");
    if (input_pointer == NULL)
    {
        fprintf(stderr, "Error opening %s\n", input_file);
        return 1;
    }

    // Initialize EOF loop
    while (fread(&rec, sizeof(BYTE), sizeof(rec), input_pointer) == sizeof(rec))
    {
        if (rec.opening[0] == 0xff && rec.opening[1] == 0xd8 && rec.opening[2] == 0xff && (rec.opening[3] & 0xf0) == 0xe0)
        {
            if (output_pointer != NULL)
            {
                fclose(output_pointer);
            }
            sprintf(name, "%03i.jpg", counter);
            counter++;
            output_pointer = fopen(name, "w");
            if (output_pointer == NULL)
            {
                fprintf(stderr, "Error opening %s\n", name);
                return 1;
            }
        }
        if (output_pointer != NULL)
        {
            fwrite(&rec, sizeof(BYTE), sizeof(rec), output_pointer);
        }
    }

    // Close open files
    fclose(input_pointer);
    if (output_pointer != NULL)
    {
        fclose(output_pointer);
    }

    // That's all folks
    return 0;
}


int EndsWith(char *string, char *suffix)
{
    // Check string + suffix are valid
    if (!string || !suffix)
    {
        return 1;
    }

    // Initialize length of string + suffix
    int string_length = strlen(string);
    int suffix_length = strlen(suffix);

    // Check if string is at least as long as suffix
    if (string_length < suffix_length)
    {
        return 1;
    }

    //return strncmp value
    return strncmp(string + string_length - suffix_length, suffix, suffix_length);
}