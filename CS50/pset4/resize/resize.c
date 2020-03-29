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
    printf("%s", argv[1]);
    int n = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    BITMAPFILEHEADER bfo = bf;
    BITMAPINFOHEADER bio = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    //storing padding value for infile
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;


    //updating file and info header parameters
    bio.biWidth = bi.biWidth * n;
    bio.biHeight = bi.biHeight * n;

    // determine padding for resized image
    int padding_2 = (4 - (bio.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //updating overall size in bytes of the image, then factoring that into file header size in bytes
    bio.biSizeImage = ((sizeof(RGBTRIPLE) * bio.biWidth) + padding_2) * abs(bio.biHeight);
    bfo.bfSize = bio.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bfo, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bio, sizeof(BITMAPINFOHEADER), 1, outptr);


    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        //repeat process for how many rows you need to copy into outfile up to the last row
        for (int k = 0; k < n-1; k++)
        {

            //iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                //temporary storage
                RGBTRIPLE triple;

                //read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                for (int l = 0; l < n; l++)
                {
                    //write RGB triple to outfile n times
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }

            }

            //skip over padding in infile row
            fseek(inptr, padding, SEEK_CUR);

            //adding padding to outfile completed row
            for (int m = 0; m < padding_2; m++)
            {
                fputc(0x00, outptr);

            }

            //need to send fread pointer back to first pixel of row to start process again, remember fread has only iterated over pixels and NO padding
            fseek(inptr, -1*sizeof(RGBTRIPLE)*bi.biWidth-padding, SEEK_CUR);

        }


        for (int x = 0; x < bi.biWidth; x++)
        {
            RGBTRIPLE triple;

            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            for (int l = 0; l < n; l++)
                {//write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }


        }

        for (int m = 0; m < padding_2; m++)
            {
                fputc(0x00, outptr);

            }

        fseek(inptr, padding, SEEK_CUR);


        }


    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
