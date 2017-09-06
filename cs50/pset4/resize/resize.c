#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

#define MAX_SIZE 100
#define MIN_SIZE 0

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./copy infile outfile\n");
        return 1;
    }

    // remember filenames and resize argument
    int resize =atof(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];
    
    if (resize >MAX_SIZE || resize<MIN_SIZE)
    {
        fprintf(stderr, "Wrong resize index\n");
        return 1;
    }

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 1;
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
        return 4;
    }

    // write outfile's BITMAPFILEHEADER
//    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    
//необходимо внести сюда изменения в частности в bi.biWidth; bi.biHeight, сохранив при этом старые парраметры
    LONG old_W = bi.biWidth;
    LONG old_H = bi.biHeight;
    bi.biWidth*=resize;
    bi.biHeight*=resize;
   
    


    // determine padding for scanlines
    int padding = (4 - (old_W * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding_r = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    fpos_t position;
    // iterate over infile's scanlines
//    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
     bi.biSizeImage=((sizeof(RGBTRIPLE)*bi.biWidth)+padding_r)*abs(bi.biHeight);
     bf.bfSize=bi.biSizeImage+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
     fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);    
    
    for (int i = 0, biHeight = abs(old_H); i < biHeight; i++)
    {
        // iterate over pixels in scanline
//        for (int j = 0; j < bi.biWidth; j++)
        fgetpos (inptr, &position); 
        for (int m=0; m<resize; m++)
        {   int count=0;
            fsetpos(inptr, &position);
            for (int j = 0; j < old_W; j++)
            {
                
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
                // write RGB triple to outfile            

                for (int k=0; k<resize; k++){
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    count++;
                }
            }
            // add padding
            count*=3;
            if ((count%4)!=0){
                for (int k = 0; k < padding_r; k++)
                    fputc(0x00, outptr);
            }   
        }
        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

    }
    bf.bfSize=bi.biSizeImage+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
