/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>

#include "helpers.h"
#define LIMIT 65536

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    //initialize start + end position
    int start = 0;
    int end = n - 1;

    //return false if n is non-positive
    if (n < 1)
    {
        return false;
    }

    //binary search of array
    while (start <= end)
    {
        //search for value halfway through array
        if (values[(start+end)/2] == value)
        {
            return true;
        }

        //disregard first half of remaining array
        else if (values[(start+end)/2] < value)
        {
            start = ((start + end)/2) + 1;
        }

        //disregard second half of remaining array
        else
        {
            end = ((start+end)/2) - 1;
        }
    }

    return false;

}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    //declare count array
    int count_array[LIMIT] = {0};

    //loop values into count array
    for (int i = 0; i < n; i++)
    {
        count_array[values[i]]++;
    }

    //loop count array back into values
    int pos = 0;
    for (int j = 0; j < LIMIT; j++)
    {
        while (count_array[j] != 0)
        {
            values[pos] = j;
            pos++;
            count_array[j]--;
        }
    }

    return;
}