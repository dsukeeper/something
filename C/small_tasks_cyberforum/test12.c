#include <stdio.h>
#include <stdlib.h>
 
int CreateFile(void)
{
    int i;
    float b;
    int x=0;
 
    printf("Please enter line value:");
    scanf("%i", &x);
 
    FILE *file = fopen("file.txt", "w");
 
    for (i = 0; i<x; i++)
    {
        scanf("%f", &b);
        fwrite(&b, sizeof(float),1, file);
    }
 
    fclose(file);
    return x;
}
 
void PrintFile(int x, float *p)
{
    int i;
    FILE *file = fopen("file.txt", "r");
    
    for (i = 0; i < x; i++)
    {
        fread((p+i), sizeof(float),1, file);
        printf("\n%2d) %4.2f", i, *(p+i));
    }

 
    fclose(file);
}
 
int main()
{
    int size;
    size = CreateFile();
    float *p = malloc(size*sizeof(float));
    PrintFile(size, p);
    free(p);
    return 0;
}