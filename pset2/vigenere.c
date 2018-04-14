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

    else
    {
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (!isalpha(argv[1][i])) // check if the key is alphabetical
            {
                printf("Usage: Only use alphabetical characters\n");
                return 1;
            }
        }
    }

    string key = argv[1];
    int keylen = strlen(key); // store user key length

    input = get_string("Enter a message to encrypt: "); // Prompt user for input
    printf("ciphertext: ");

    for (int i = 0, j = 0, n = strlen(input); i < n; i++)
    {
        int cipher = tolower(key[j % keylen]) - 'a';
        //get key for letter input

        if islower(input[i])
        {
            // keep lowercase
            printf("%c", 'a' + (input[i] - 'a' + cipher) % 26);
            j++;
        }

        else if isupper(input[i])
        {
            // Keep uppercase
            printf("%c", 'A' + (input[i] - 'A' + cipher) % 26);
            j++;
        }

        else
        {
            // return leftovers
            printf("%c", input[i]);
        }

    }
    printf("\n");
    return 0;
}
