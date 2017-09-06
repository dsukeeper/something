#include <cs50.h>
#include <stdio.h>
int main (void){
    int level;

    do {
        printf("Height:");
        level = get_int();
    }
    while ((level<0) || (level>23));
    
        for (int i=0; i <level; i++){
            for (int k=0; k<level-i-1; k++)
                    printf(" ");
            for (int j=0; j<=i; j++)
                printf("#");
            printf ("  ");
            for (int j=0; j<=i; j++)
                printf("#");
            printf("\n");
        } 
}


