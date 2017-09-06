#include <stdio.h>
#include <stdlib.h>

#define MAX 10


int main(int argc, char *argv[]){
    
    int *ptr= malloc(2*sizeof(int));

    if (argc != 3)
    {
        fprintf(stderr, "Usage: ./numbers infile outfile \n");
        return 1;
    }

    char *infile = argv[1];
    char *outfile = argv[2];
    
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }
    
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }
    int i=1;
    do{
        
        fread(ptr,sizeof(int),2,inptr);
        printf ("%i %i", *ptr, *(ptr+1));
        if ((i%2)==0)
            fwrite(ptr,sizeof(int),2,outptr);
        i++;
    }while (*(ptr+1)!=0 || *ptr!=0); 
    
    
    fclose(inptr);
    fclose(outptr);
    free(ptr);   
    
}