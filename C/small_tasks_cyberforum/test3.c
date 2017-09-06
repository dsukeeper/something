#include <stdio.h>
#define N 10
int main()
{
    
    float a[N]={1.2,2.2,3.3,4.4,5.5,6.6,7.7,8.8,99.9,10.1}, *p,*pmin,*pmax;
    
    pmax=a;
    pmin=pmax;
    for(p=a;p<a+N;p++)
    {
    if(*p>*pmax)
        pmax=p;
    if(*p<*pmin)
        pmin=p;
    }
    if(pmax>a+N/2) printf("\nmaximum sprava =%1.1f",*pmax);
    else printf("\nmaximum sleva =%1.1f",*pmax);
    if(pmin>a+N/2) printf("\nminimum sprava =%1.1f",*pmin);
    else printf("\nminimum sleva =%1.1f",*pmin);
    return 0;
}