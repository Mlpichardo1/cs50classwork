#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt user for a positve number
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while(n <= 23);
    // Print out this many rows
    for (int i = 0; i < n; i++)
    {
        // Print out this many columns
        for (int j = 0; j > 0; j++)
        {
           printf("##\n");
        }
        printf("#\n");
    }
}