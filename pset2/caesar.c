//Peer Review SS

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
    //PRSS: check is 2 arguments are entered on command line
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
        //prss: placeholder for text to print after enciphered?

        for (int i = 0, n = strlen(input); i < n; i++)
        {
            char cipher = input[i];
            //pr ss: variable to hold each character as it's enciphered?

            //check if the letter is uppercase or lowercase then convert
            if islower(input[i])
            {
                cipher = (((input[i] + key) - 97) % 26) + 97;
                //prss: transform char to ascii, to alpha then to enciphered ascii
            }

            if isupper(input[i])
            {
                cipher = (((input[i] + key) - 65) % 26) + 65;
                //prss: transform char to ascii, to alpha then to enciphered ascii
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
                //prss: if [i] is not a letter print char as is
            }

        }

        printf("\n");
        return 0;

    }

}