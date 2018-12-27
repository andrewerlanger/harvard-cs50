#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{

    // Declare these guys
    BITMAPFILEHEADER bf;
    BITMAPINFOHEADER bi;

    // Check for correct usage
    if (argc != 3)
    {
        fprintf(stderr, "correct usage: ./whodunit input_file output_file\n");
        return 1;
    }

    // Initialize input + output files
    char *input_file = argv[1];
    char *output_file = argv[2];

    // Open input file + error-check
    FILE *input_ptr = fopen(input_file, "r");
    if (input_ptr == NULL)
    {
        fprintf(stderr, "can't open %s\n", input_file);
        return 2;
    }

    // Open output file
    FILE *output_ptr = fopen(output_file, "w");
    if (output_ptr == NULL)
    {
        fprintf(stderr, "can't open %s\n", output_file);
        return 3;
    }

    // Read BITMAPFILEHEADER + BITMAPINFOHEADER
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, input_ptr);
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, input_ptr);

    // Check file is BMP
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(input_ptr);
        fclose(output_ptr);
        fprintf(stderr, "looks like %s is not a BMP file\n", input_file);
        return 4;
    }

    // Write BITMAPFILEHEADER + BITMAPINFOHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, output_ptr);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, output_ptr);

    // Determine padding
    int padding = (4 - ((bi.biWidth * sizeof(RGBTRIPLE)) % 4)) % 4;

    // Iterate over input file's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // Iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // Temporary storage
            RGBTRIPLE triple;

            // Read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, input_ptr);

            // Check for red values, and add if necessary
            if (triple.rgbtRed == 0xff)
            {
                triple.rgbtRed = 0x00;
            }

            // Write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, output_ptr);
        }

        // Skip over padding, if any
        fseek(input_ptr, padding, SEEK_CUR);

        // Then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, output_ptr);
        }
    }

    // Close infile
    fclose(input_ptr);

    // Close outfile
    fclose(output_ptr);

    // That's all folks
    return 0;

}