/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n<0) 
        return false;
    int begin_value, end_value, mid;
    int i_beg=0;
    int i_end=n-1;    
    begin_value=values[0];
    end_value=values[n-1];
    if (value==begin_value || value == end_value)
        return true;

    
    while (value>=begin_value && value<=end_value){

        
        mid=i_beg + (i_end-i_beg)/2;
        
        if(value==values[mid])
            return true;
            
        if(value>=values[mid]){
            begin_value=values[mid];
            i_beg=mid;
        }
        else {
            end_value=values[mid];
            i_end=mid;
        }
            
        if ((i_end-i_beg)==1){
            if (value==begin_value)
                return true;
            else {
                if (value==end_value)
                    return true;
                else 
                    return false;
            }
        }
        
    
        
    }
    return false;
}


/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    for (int j=n-1;j>0;j--){
        for (int i=0;i<j;i++){
            if(values[i]>values[i+1]){
                int temp = values[i];
                values[i]=values[i+1];
                values[i+1]=temp;
            }       
        }
    }
    return;
}
