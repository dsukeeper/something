#include <stdio.h>
int main(void)
{
    int a=55;
    int b=3;
    if (a>b && b<0 )
        b=0;
    else b=1;
    
    if (a<b && a<0)
        a=0;
    if (a<b && a>0) 
        a=1;
    printf("a= %i \nb= %i \n",a,b);
}
