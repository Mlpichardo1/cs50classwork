#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    // Prompt user for a positve number
    do
    {
        height = get_int("Choose the Height for my Pyramid: ");fsd
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

// Line 11: after semi-colon you have 'fsd'. This throws an error.
// Be sure to use style50 and check50 before you submit50, to help catch little things like this.
// Maybe a comment at the top to summarize the program, what it does
// Maybe comment variables as they're declared.
// I say maybe because I am not sure. I know that they want us to comment, but I have heard devs complain about
// too many comments or overly simple comments :)