#include <cs50.h>
#include <stdio.h>

int main (void){
    int Minutes;
    printf("Minutes:");
    do
        Minutes = get_int();
    while (Minutes<0);

    int Bottles = 12*Minutes;
    printf ("bottles:` %i", Bottles);

}