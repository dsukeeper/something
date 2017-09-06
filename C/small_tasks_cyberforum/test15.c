/*Есть два одномерных целочисленных массива, задание состоит в том, 
чтобы заменить в них местами соответствующие элементы */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

void memarr(int *arr1, int *arr2, int size1, int size2, int max)
{
    int *arr_t = malloc (max*sizeof(int));
    memcpy (arr_t, arr1, size1*sizeof(int));
    memcpy (arr1, arr2, size2*sizeof(int));
    memcpy (arr2, arr_t, size1*sizeof(int));
    free(arr_t);
    
}

void printarr (int *arr, int len)
{
    for (int i=0; i<len; i++)
        printf("%i", *(arr+i));
    printf("\n");
}

void fillMasRand(int *m, int c)
{
    for(int i=0;i<c; i++)
        m[i]=rand()%10;
}


int main(void)
{   
    int size_arr1 = 10;
    int size_arr2 = 5;
    int *arr1 = malloc (size_arr1*sizeof(int));
    int *arr2 = malloc (size_arr1*sizeof(int));

    srand(time(NULL));
    fillMasRand(arr1, size_arr1);
    fillMasRand(arr2, size_arr2);
    
    printarr(arr1, size_arr1);
    printarr(arr2, size_arr2);
    
    if (size_arr1>size_arr2)
    {
        arr2=realloc(arr2, size_arr1);
        memarr(arr1, arr2, size_arr1, size_arr2, size_arr1);
    }
    else 
    {
        arr1=realloc(arr1, size_arr2);
        memarr(arr2, arr1, size_arr2, size_arr1, size_arr2); 
    }
        

    
    printarr(arr1, size_arr2);
    printarr(arr2, size_arr1);
    
    free(arr1);
    free(arr2);
}
