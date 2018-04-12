#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main()
{

    string input;
    int i, key;

    do
    {
        // Prompt user for Name
        input = get_string("Enter a message to encrypt: ");
        key = get_int("Enter key: ");
    }
    while (input < 0);

    char encrpyt;
    // iterate through user input
      for(i = 0; input[i] != '\0'; ++i){
        encrpyt = input[i];

        if(encrpyt >= 'a' && ch <= 'z'){
            encrpyt = encrpyt + key;

            if(encrpyt > 'z'){
                encrpyt = encrpyt - 'z' + 'a' - 1;
            }

            input[i] = encrpyt;
        }
        else if(encrpyt >= 'A' && encrpyt <= 'Z'){
            encrpyt = encrpyt + key;

            if(encrpyt > 'Z'){
                encrpyt = encrpyt - 'Z' + 'A' - 1;
            }

            input[i] = encrpyt;
        }
    }
    printf("Encrypted message: %s", encrpyt);
    printf("\n");
}