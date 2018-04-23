// Helper functions for music

#include <cs50.h>
#include <math.h>
#include <ctype.h>
#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int x = fraction[0]; // stores fraction X
    int y = fraction[2]; // stores fraction Y

    if (x == '1')
    {
        if (y == '8')
        {
            return 1;
        }
        else if (y == '4')
        {
            return 2;
        }
        else if (y == '2')
        {
            return 4;
        }
        else if (y == '1')
        {
            return 8;
        }
    }
    else if (x == '3' && y == '8')
    {
        return 3;
    }
    else
    {
        return 0;
    }
    return 0;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    char lngletter[3]; // For notes containing an accidental
    char letter[2]; // Notes w/out an accidental
    char octave[2];

    if (isdigit(note[1]))
    {
        letter[0] = note[0];
        letter[1] = '\0';
        octave[0] = note[1];
        octave[1] = '\0';
    }
    else if (!isdigit(note[1]))
    {
        lngletter[0] = note[0];
        lngletter[1] = note[1];
        lngletter[2] = '\0';
        octave[0] = note[2];
        octave[1] = '\0';
    }

    float newoctave = atoi(octave);
    double frequency;
    int n = 12.0;

    switch (note[0]) // examine which Note letter
    {
        case 'C' :
            frequency = 440.0 / (pow(2.0, (9.0 / n)));
            break;
        case 'D' :
            frequency = 440.0 / (pow(2.0, (7.0 / n)));
            break;
        case 'E' :
            frequency = 440.0 / (pow(2.0, (5.0 / n)));
            break;
        case 'F' :
            frequency = 440.0 / (pow(2.0, (4.0 / n)));
            break;
        case 'G' :
            frequency = 440.0 / (pow(2.0, (2.0 / n)));
            break;
        case 'A' :
            frequency = 440.0;
            break;
        case 'B' :
            frequency = 440.0 * (pow(2.0, (2.0 / n)));
            break;
        default :
            return 0;
    }

    // Loop to shift octave up or down
    if (newoctave > 4)
    {
        for (int i = 0; i < newoctave - 4; i++)
        {
            frequency *= 2.0;
        }
    }
    else if (newoctave < 4)
    {
        for (int i = 0; i < 4 - newoctave; i++)
        {
            frequency /= 2.0;
        }
    }

    // If accidental is flat or sharp
    if (note[1] == 'b')
    {
        frequency /= (pow(2.0, (1.0 / n)));
    }
    else if (note[1] == '#')
    {
        frequency *= (pow(2.0, (1.0 / n)));
    }

    // Return frequency value as an int
    int synth = round(frequency);
    return synth;

}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (s[0] == '\0') // Check if s is blank
    {
        return true;
    }
    return false;
}
