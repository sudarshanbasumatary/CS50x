/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

// void print_header(BITMAPFILEHEADER bf, BITMAPINFOHEADER bi) {
//     printf("\nHeader INFO\nFILE:\n%d\n%d\n%d\n%d\n%d\nINFO:\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",
//         bf.bfType, bf.bfSize, bf.bfReserved1, bf.bfReserved2, bf.bfOffBits,
//         bi.biSize, bi.biWidth, bi.biHeight, bi.biPlanes, bi.biBitCount, bi.biCompression, bi.biSizeImage, bi.biXPelsPerMeter, bi.biYPelsPerMeter, bi.biClrUsed, bi.biClrImportant);
    
// }

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy resizeFactor infile outfile\n");
        return 1;
    }

    // remember filenames
    int resizeFactor = atoi(argv[1]);
    if(resizeFactor < 1 || resizeFactor > 100) {
        printf("Invalid resize factor!");
        return 1;
    }
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf, newBf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, newBi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    newBf = bf;
    newBi = bi;
    newBi.biWidth = newBi.biWidth * resizeFactor;
    newBi.biHeight = newBi.biHeight * resizeFactor;

    // determine padding for scanlines
    int padding =  ((4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4);
    int newPadding = (4 - (newBi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    newBi.biSizeImage = (abs(newBi.biHeight) * newBi.biWidth) * (bi.biBitCount / 8) + abs(newBi.biHeight) * newPadding;
    newBf.bfSize = 54 + newBi.biSizeImage;
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&newBf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&newBi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // print_header(bf,bi);print_header(newBf,newBi);
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        RGBTRIPLE scanlineTriples[newBi.biWidth];
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;
            
            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            for(int k = 0; k < resizeFactor; k++)
                scanlineTriples[j * resizeFactor + k] = triple;
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // write RGB scanline to outfile resizeFactor number of times
        for(int l = 0; l < resizeFactor; l++) 
        {
            fwrite(scanlineTriples, sizeof(RGBTRIPLE), newBi.biWidth, outptr);
            
            // then add it back (to demonstrate how)
            for (int k = 0; k < newPadding; k++)
            {
                fputc(0x00, outptr);
            }
        }
        
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
