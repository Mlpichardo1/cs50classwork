//PeerReview SS
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string name;

    do
    {
        // Prompt user for Name
        name = get_string();
    }
    while (name < 0);

    int length = strlen(name);
    // Print the 1st Character of name
    //prss: Print 1st char in name in uppercase
    if (name[0] != ' ' && name[0] != '\0')
    {
        printf("%c", toupper(name[0]));
    }
    // Loop over the string, character by character
    //prss: loop through name, character by character
    for (int i = 0; i < length; i++)
        // check if character is a whitespace and print second letter
        //prss": check if character is a whitespace
        if (!isalpha(name[i]))
        {
            //prss: if whitespace, print next char in uppercase
            printf("%c", toupper(name[i + 1]));
        }
    printf("\n");
}
