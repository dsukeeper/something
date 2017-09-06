#include <stdio.h>
#define MAX 20 // максимальное кол-во элементов 



int main() {
    int a[MAX]={20,100,18,17,16,15,14,13,12,11,19,9,8,50,6,5,4,3,2,19};
    int a1=0, a2=0;
    
    a1=a[0];
    a2=a[1];
    for (int i=1; i<MAX; i++){
        if (a[i]>a1){
            a2=a1;
            a1=a[i];
        }
         else 
            if (a[i]>a2)
                a2=a[i];
    }
    printf("%i\n",a2);

}