#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    string input;

    do
    {
        // prompt user for input
        input = get_string();
    }
    while (argc < 1);

    int length = strlen(input);
    int k = atoi(argv[2]);

    // iterate through user input
    for (int i = 0; i < length; i++)
    {
        if (islower(input[i]))
        {
            printf("%c", (input[i] + k));
        }
        else (isupper(input[i]));
        {
            printf("%c", (input[i] + k));
        }
        printf("\n");
    }
}

// isalpha
// isupper
