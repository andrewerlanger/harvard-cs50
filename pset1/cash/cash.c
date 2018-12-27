#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main(void)
{

    float change;

    // Prompt user for amount of change owed until positive float provided
    do
    {
        printf("How much change is owed?\n");
        change = get_float();
    }
    while (change < 0);

    // Convert float to integer
    int change_int = (int)round(change * 100);
    int coins = 0;

    // Calculate number of quarters in change
    while (change_int >= 25)
    {
        change_int -= 25;
        coins++;
    }

    // Calculate number of dimes in change
    while (change_int >= 10)
    {
        change_int -= 10;
        coins++;
    }

    // Calculate number of nickels in change
    while (change_int >= 5)
    {
        change_int -= 5;
        coins++;
    }

    // Calculate number of pennys in change
    while (change_int >= 1)
    {
        change_int -= 1;
        coins++;
    }

    // Print minimum number of coins required in change
    printf("It turns out you need %i coins in total\n", coins);
}