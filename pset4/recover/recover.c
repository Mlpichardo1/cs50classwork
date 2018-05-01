#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 512

int main(void)
{
    // open memory card
    FILE *input = fopen("card.raw", "r");
    if (input == NULL)
    {
        printf("Unable to open card.raw.\n");
        return 1;
    }

    // create buffer
    unsigned char buffer[BUFFER_SIZE];

    // filename counter
    int filecount = 0;

    FILE *pic = NULL;

    // check if we've found a jpeg
    int jpg = 0; //false

    // go through cardfile until there aren't any blocks left
    while (fread(buffer, BUFFER_SIZE, 1, input) == 1)
    {
        // read first 4 bytes of buffer and see if jpg signature using bitwise on last byte
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xe0) == 0xe0)
        {
            if (jpg == 1)
            {
                // The start is found, so close out current picture
                fclose(pic);
            }
            else
            {
                // jpg is found now write out
                jpg = 1;
            }

            char filename[8];
            sprintf(filename, "%03d.jpg", filecount);
            pic = fopen(filename, "a");
            filecount++;
        }

        if (jpg == 1)
        {
            // write 512 bytes to file
            fwrite(&buffer, BUFFER_SIZE, 1, pic);
        }

    }

    // close infile
    fclose(input);

    // close outfile
    fclose(pic);

    // success
    return 0;
}