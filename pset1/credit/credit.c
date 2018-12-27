#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

int main(void)
{
    // Declare variables
    char char_number[30];
    long long number;

    // Prompt user for credit card number
    while (true)
    {
        printf("What is your credit card number?\n");
        fgets(char_number, sizeof(char_number), stdin);
        if (sscanf(char_number, "%lld", &number) != 1)
        {
            printf("invalid credit card number. try again.\n");
        }
        else
        {
            break;
        }
    }

    // Calculate length of number and declare array
    int counter = strlen(char_number) - 1;
    int array[counter];

    for (int i = 0; i < counter; i++)
    {
        array[i] = number % 10;
        number = number / 10;
    }

    long long sum1 = 0;
    int temp;

    for (int j = 1; j < counter; j = j + 2)
    {
        temp = 2 * array[j];
        while (temp != 0)
        {
            sum1 = sum1 + (temp % 10);
            temp = temp / 10;
        }

    }

    long long sum2 = 0;

    for (int k = 0; k < counter; k = k + 2)
    {
        sum2 = sum2 + array[k];
    }

    long long sum3 = sum1 + sum2;

    // if (array[counter - 1] == 3)
    // {
    //     printf("AMEX\n");
    // }
    // else if (array[counter - 1] == 4)
    // {
    //     printf("VISA\n");
    // }
    // else if (array[counter - 1] == 5)
    // {
    //     printf("MASTERCARD\n");
    // }
    // else
    // {
    //     printf("INVALID\n");
    //     return 0;
    // }

    int first_two_digits = (array[counter - 1] * 10) + array[counter - 2];

    if (sum3 % 10 == 0)
    {
        if (counter == 15 && (
                first_two_digits == 34 ||
                first_two_digits == 37))
        {
            printf("AMEX\n");
        }
        else if (counter == 16 && (
                     first_two_digits == 51 ||
                     first_two_digits == 52 ||
                     first_two_digits == 53 ||
                     first_two_digits == 54 ||
                     first_two_digits == 55))
        {
            printf("MASTERCARD\n");
        }
        else if ((counter == 13 || counter == 16) && array[counter - 1] == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
            return 0;
        }
    }
    else
    {
        printf("INVALID\n");
    }
}