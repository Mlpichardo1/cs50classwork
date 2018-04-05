#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Prompt user for a positve number
    int n;
    do
    {
        n = get_int("Postive Number: ");
    }
    while(n <= 0);
    // Print out this many rows
    for (int i = 0; i < 4; i++)
    {
        // Print out this many columns
        for (int j = 0; j < 0; j++)
        {
           printf("#");
        }
        printf("\n");
    }
}