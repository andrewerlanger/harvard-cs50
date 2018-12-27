// Helper functions for music

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int length = strlen(fraction);
    float numerator = atoi(&fraction[0]);
    float denominator = atoi(&fraction[length - 1]);

    int duration = (numerator / denominator) * 8;
    return duration;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    //calculate length
    int note_length = strlen(note);

    //determine octave + letter
    int octave = atoi(&note[note_length - 1]);
    char letter = note[0];

    //calculate # semitones from A4
    float n = (octave - 4) * 12;

    if (letter == 'B')
    {
        n += 2;
    }
    else if (letter == 'C')
    {
        n -= 9;
    }
    else if (letter == 'D')
    {
        n -= 7;
    }
    else if (letter == 'E')
    {
        n -= 5;
    }
    else if (letter == 'F')
    {
        n -= 4;
    }
    else if (letter == 'G')
    {
        n -= 2;
    }

    //take the accidentals into consideration
    if (note[1] == '#')
    {
        n++;
    }
    else if (note[1] == 'b')
    {
        n--;
    }

    //test frequency
    double frequency = pow(2, n / 12) * 440;
    int rounded_frequency = round(frequency);
    return rounded_frequency;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (s[0] == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
