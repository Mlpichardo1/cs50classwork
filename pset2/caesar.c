#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{

    string input; // store user input

    if (argc != 2)
    {
        printf("Usage: enter key\n"); // Alert user if key is not entered properly
        return 1;
    }

    int key = atoi(argv[1]); // store user key number

    if (key < 0) // check if the integer is non-negative
    {
        printf("Try again\n");
        return 1;
    }

    else
    {

        input = get_string("Enter a message to encrypt: "); // Prompt user for input
        printf("ciphertext: ");

        for (int i = 0, n = strlen(input); i < n; i++)
        {
            char cipher = input[i];
            //check if the letter is uppercase or lowercase then convert

            if islower(input[i])
            {
                cipher = (((input[i] + key) - 97) % 26) + 97;
            }

            if isupper(input[i])
            {
                cipher = (((input[i] + key) - 65) % 26) + 65;
            }

            //if neither then just print whats left
            if (isalpha(input[i]))
            {
                input[i] = cipher;
                printf("%c", cipher);
            }

            else
            {
                printf("%c", cipher);
            }

        }

        printf("\n");
        return 0;

    }

}