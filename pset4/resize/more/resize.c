#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "bmp.h"

int EndsWith(const char *full_file, const char *suffix);

int main(int argc, char *argv[])
{
    // Initialize key variables
    int temp, temp2;
    float temph, tempw, original_height, new_height, original_width, new_width;
    RGBTRIPLE triple;

    // Check argc == 4
    if (argc != 4)
    {
        fprintf(stderr, "correct usage: ./resize3 f input.bmp output.bmp\n");
        return 1;
    }

    // Convert argv[1] to float + check value
    float f = atof(argv[1]);
    if (f <= 0 || f > 100)
    {
        printf("0 < f <= 100\n");
        return 1;
    }

    // Capture input + output files as strings
    char *input_file = argv[2];
    char *output_file = argv[3];

    // Check input + output files have .bmp extension
    if (EndsWith(input_file, ".bmp") != 0 || EndsWith(output_file, ".bmp") != 0)
    {
        fprintf(stderr, "Both files need to have .bmp extensions\n");
        return 1;
    }

    // Open input + output files
    FILE *input_pointer = fopen(input_file, "r");
    if (input_pointer == NULL)
    {
        fprintf(stderr, "input pointer is NULL\n");
        return 1;
    }
    FILE *output_pointer = fopen(output_file, "w");
    if (output_pointer == NULL)
    {
        fprintf(stderr, "output pointer is NULL\n");
        return 1;
    }

    // Read BITMAPFILEHEADER + BITMAPINFOHEADER
    BITMAPFILEHEADER bf_original;
    fread(&bf_original, sizeof(BITMAPFILEHEADER), 1, input_pointer);
    BITMAPINFOHEADER bi_original;
    fread(&bi_original, sizeof(BITMAPINFOHEADER), 1, input_pointer);
    BITMAPFILEHEADER bf_new = bf_original;
    BITMAPINFOHEADER bi_new = bi_original;

    // Double-check input file is .bmp
    if (bf_original.bfType != 0x4d42 || bf_original.bfOffBits != 54 || bi_original.biSize != 40 ||
        bi_original.biBitCount != 24 || bi_original.biCompression != 0)
    {
        fprintf(stderr, "oops, looks like %s isn't a BMP file\n", input_file);
        return 1;
    }

    // Calculate new width + height values
    bi_new.biWidth = round(bi_original.biWidth * f);
    bi_new.biHeight = round(bi_original.biHeight * f);

    // Calculate original + new padding values
    int padding_original = (4 - (sizeof(RGBTRIPLE) * bi_original.biWidth) % 4) % 4;
    int padding_new = (4 - (sizeof(RGBTRIPLE) * bi_new.biWidth) % 4) % 4;

    // Calculate new image + file sizes
    bi_new.biSizeImage = ((sizeof(RGBTRIPLE) * bi_new.biWidth) + padding_new) * abs(bi_new.biHeight);
    bf_new.bfSize = bi_new.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // Write new values to output file
    fwrite(&bf_new, sizeof(BITMAPFILEHEADER), 1, output_pointer);
    fwrite(&bi_new, sizeof(BITMAPINFOHEADER), 1, output_pointer);

    // Define height floats
    original_height = abs(bi_original.biHeight);
    new_height = abs(bi_new.biHeight);

    // Path 1: f greater than (or equal to) 1
    if (f >= 1)
    {
        // Loop for columns
        for (int i = 0; i < abs(bi_original.biHeight); i++)
        {

            // Initialize temp2
            temp2 = round(new_height / original_height);

            // How many times are we writing this row
            for (int z = 0; z < temp2; z++)
            {

                // Initialize width floats
                original_width = bi_original.biWidth;
                new_width = bi_new.biWidth;

                // Write the row
                for (int j = 0; j < bi_original.biWidth; j++)
                {
                    fread(&triple, sizeof(RGBTRIPLE), 1, input_pointer);
                    temp = round(new_width / original_width);
                    for (int x = 0; x < temp; x++)
                    {
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, output_pointer);
                    }
                    original_width--;
                    new_width -= temp;
                }

                // Write new padding
                for (int k = 0; k < padding_new; k++)
                {
                    fputc(0x00, output_pointer);
                }

                // Move cursor back to start of row
                if (z < temp2 - 1)
                {
                    fseek(input_pointer, -(bi_original.biWidth * sizeof(RGBTRIPLE)), SEEK_CUR);
                }
            }
            // Skip over padding
            fseek(input_pointer, padding_original, SEEK_CUR);

            // Adjust height values
            new_height -= temp2;
            original_height--;
        }
    }

    // Path 2: f less than 1
    else if (f < 1)
    {
        fprintf(stdout, "start: %li\n", ftell(input_pointer));
        // Loop for columns
        for (int i2 = 0; i2 < abs(bi_new.biHeight); i2++)
        {
            // Seek to first row we'll write from
            temph = round(original_height / (new_height));
            fseek(input_pointer, (temph - 1) * ((sizeof(RGBTRIPLE) * bi_original.biWidth) + padding_original), SEEK_CUR);
            fprintf(stdout, "after column seek: %li\n", ftell(input_pointer));

            // Define widths
            original_width = bi_original.biWidth;
            original_width = bi_original.biWidth;
            new_width = bi_new.biWidth;

            // Loop for rows
            for (int j2 = 0; j2 < bi_new.biWidth; j2++)
            {
                tempw = round(original_width / new_width);
                fseek(input_pointer, (tempw - 1)*sizeof(RGBTRIPLE), SEEK_CUR);
                fread(&triple, sizeof(RGBTRIPLE), 1, input_pointer);
                fwrite(&triple, sizeof(RGBTRIPLE), 1, output_pointer);
                fprintf(stdout, "after write: %li\n", ftell(input_pointer));
                original_width -= tempw;
                new_width--;
            }

            // Write new padding
            for (int k2 = 0; k2 < padding_new; k2++)
            {
                fputc(0x00, output_pointer);
            }
            fprintf(stdout, "after padding (output): %li\n", ftell(output_pointer));

            // Skip over padding
            fseek(input_pointer, padding_original, SEEK_CUR);
            fprintf(stdout, "after padding: %li\n", ftell(input_pointer));

            // Adjust height values
            original_height -= temph;
            new_height--;
        }

    }

    // Close files
    fclose(input_pointer);
    fclose(output_pointer);

    // That's all folks
    return 0;

}

int EndsWith(const char *full_file, const char *suffix)
{
    if (!full_file || !suffix)
    {
        fprintf(stderr, "EndsWith error\n");
        return 1;
    }

    int full_file_length = strlen(full_file);
    int suffix_length = strlen(suffix);

    if (full_file_length < suffix_length)
    {
        fprintf(stderr, "File length error\n");
        return 1;
    }

    return strncmp(full_file + full_file_length - suffix_length, suffix, suffix_length);
}