#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // remember filenames
    int n = atoi(argv[1]); // accept and Integer for input
    char *infile = argv[2];
    char *outfile = argv[3];

    // check for value of n 1-100
    if (n < 0 || n > 100)
    {
        printf("Enter a number between 0 and 100.");
        return 2;
    }

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }

    // update new file headers
    BITMAPFILEHEADER bfResize = bf;
    BITMAPINFOHEADER biResize = bi;
    biResize.biWidth *= n;
    biResize.biHeight *= n;

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int paddingResize = (4 - (biResize.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Re Size image
    biResize.biSizeImage = (sizeof(RGBTRIPLE) * biResize.biWidth + paddingResize) * abs(biResize.biHeight);
    bfResize.bfSize = biResize.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bfResize, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&biResize, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        for (int vertical = 0; vertical < n; vertical++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                for (int horizontal = 0; horizontal < n; horizontal++)
                {
                    // write RGB triple to outfile//  WIDTH is taken
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);

            // then add it back (to demonstrate how) Resized Padding
            for (int k = 0; k < paddingResize; k++)
            {
                fputc(0x00, outptr);
            }

            if (vertical < n - 1)
            {
                fseek(inptr, -(bi.biWidth * 3 + padding), SEEK_CUR);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}