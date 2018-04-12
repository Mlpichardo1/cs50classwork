#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    // Prompt user for a positve number
    do
    {
        height = get_int("Choose the Height for my Pyramid: ");
    }
    while (height < 0 || height > 23);
    // Print out this many rows
    for (int row = 0; row < height; row++)
    {
        // Print out this many columns
        for (int space = height - row; space > 1; space--)
        {
            printf(" ");
        }
        // Print Blocks for pyramid
        for (int blocks = 0; blocks < row + 2; blocks++)
        {
            printf("#");
        }
        printf("\n");
    }
}