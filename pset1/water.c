#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Prompt user for minutes
    int minutes;
    int bottles = 12;
    int result;
    // Log entered minutes and times 12
    do
    {
        minutes = get_int("Minutes: ");
        result = minutes * bottles;
    }
    while (minutes <= 0);
    {
        // Display Minutes and Bottles
        printf("Minutes: %i\n", minutes);
        printf("Bottles: %i\n", result);
    }
}

// Line 19: Probably not necessary. Looks weird at run time, like an echo.
//  example: printf("Your %i minute shower uses %i bottles of water!\n", minutes, result);
// Add comment to the top explaining what the program is or does
// Comments seem out of place, I would put them on the lines they refer to.
// Good Job Manny!!!