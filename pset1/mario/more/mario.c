#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Prompt user for pyramid height
    int height = get_int("Height: ");

    // Continue prompting until height value given between 0 and 23
    while (height < 0 || height > 23)
    {
        height = get_int("Height: ");
    }

    // Print pyramid of given height
    for (int i = 0; i < height; i++)
    {
        // Blank space to the left of pyramid
        for (int j = 0; j <= height - i - 2; j++)
        {
            printf(" ");
        }

        // Left side of pyramid
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }

        // Blank space between left and right sides
        printf("  ");

        // Right side of pyramid
        for (int l = 0; l <= i; l++)
        {
            printf("#");
        }
        printf("\n");
    }
}