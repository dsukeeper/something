#include <stdio.h>
#include <cs50.h>
#include <math.h>

int 
    main(void){
//        int n =10;
        double cond=10;
        double number; 
        double number_t;
//        int ar [n];
        
        number = get_float();
        
        number = number/cond;
        printf("%f\n", modf(number, &number_t));
    }