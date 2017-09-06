#include <stdio.h>
#define MAX 5
int main (){
    int arr[MAX] = {-2,-2,-2,-2,-2};
    float result=1;
    
    
    for (int i=0; i<MAX; i++){
        if ((arr[i]>i+1) && (arr[i]<i)){
            result=result*arr[i];
        }
    }
    printf("%f \n", result);
    result=1/result;
    printf("%f", result);
}