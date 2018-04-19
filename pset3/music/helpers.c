// Helper functions for music

#include <cs50.h>
#include <math.h>
#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int x = fraction[0];
    int y = fracrion[2];

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
    // TODO
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (s[0] == "\0") // Check if s is blank
    {
        return true
    }
    return false;
}
