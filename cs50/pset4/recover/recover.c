#include <stdio.h>
#include <stdlib.h>
/*
int check (long *p){
int flag;
    if ( (*ptr==0xff) && (*(ptr+1)==0xd8) && (*(ptr+2)==0xff) && ((*(ptr+3)& 0xf0)==0xe0))
        return 1;
    else return 0;

    
}

*/
int main(int argc, char *argv[])
{
//    fpos_t pos;
    unsigned char *ptr= malloc(512);
//    long size_b=512;
    int count_jpg=0;

    
    
    if (argc != 2)
    {
        fprintf(stderr, "Drive not detected \n");
        return 1;
    }
    
    char *infile = argv[1];
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }
    
    fread(ptr, 1,512,inptr);

    do{
//        int count=0;
        
//        printf("%lu\n", *ptr);
 //       flag=check(ptr);
 // проверяем условие jpg
        if ( (*ptr==0xff) && (*(ptr+1)==0xd8) && (*(ptr+2)==0xff) && ((*(ptr+3)& 0xf0)==0xe0)){
            
            char *file_new=malloc(5);;
            sprintf(file_new,"%03i.jpg",count_jpg);
            FILE *img = fopen(file_new,"w");
            fwrite (ptr, 1,512,img);
            fread(ptr, 1,512,inptr);
            while (!( (*ptr==0xff) && (*(ptr+1)==0xd8) && (*(ptr+2)==0xff) && ((*(ptr+3)&0xf0)==0xe0))&& (!feof(inptr))) {
                fwrite (ptr, 1,512,img);
                fread(ptr, 1,512,inptr);
//                flag=check(ptr);
            } 
            count_jpg++;
            fclose(img);
            free(file_new);
        }
        
        else fread(ptr, 1,512,inptr);
            
//        if (count==100) break;

    }while (!feof(inptr));
    
        
//    printf("count jpg %i\n", count_jpg);
    
    free(ptr);
    fclose(inptr);
}