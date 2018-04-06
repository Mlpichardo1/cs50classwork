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