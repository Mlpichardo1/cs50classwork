//peer review ss

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
//prss: main takes two arguments: count and array of strings
{

    string input; // store user input

    if (argc != 2)
    //prss: check if 2 arguments are entered on command line
    {
        printf("Usage: enter key\n"); // Alert user if key is not entered properly
        return 1;
    }

    else
    //prss: if two args, iterate through argv[1], the key
    {
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (!isalpha(argv[1][i])) // check if the key is alphabetical
            {
                printf("Usage: Only use alphabetical characters\n");
                //prss: if key is not all alpha, display error, end program
                return 1;
            }
        }
    }

    string key = argv[1];
    //prss: set key to string argv[1]

    int keylen = strlen(key); // store user key length

    input = get_string("Enter a message to encrypt: "); // Prompt user for input
    printf("ciphertext: ");
    //prss: set placeholder for enciphered text

    for (int i = 0, j = 0, n = strlen(input); i < n; i++)
    {
    //prss: iterate thru user keyword

        int cipher = tolower(key[j % keylen]) - 'a';
        //get key for letter input

        if islower(input[i])
        {
            // keep lowercase
            printf("%c", 'a' + (input[i] - 'a' + cipher) % 26);
            //prss: convert char to ascii, alpha then ascii based on current char in key
            j++;
            //prss: increment key

        }

        else if isupper(input[i])
        {
            // Keep uppercase
            printf("%c", 'A' + (input[i] - 'A' + cipher) % 26);
            //prss: convert char to ascii, alpha then ascii based on current char in key
            j++;
            //prss: increment key
        }

        else
        {
            // return leftovers
            //prss: print each char that is not a letter
            printf("%c", input[i]);
        }

    }
    printf("\n");
    return 0;
}
