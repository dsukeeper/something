#include <stdio.h>

#define MAX 20

int main(void)
{
    char s[MAX];
    int count = 0, i=0;
    while ((c=getchar())!='\n'){
        i++;
    }
    
    if (i>=MAX-2)
        s[MAX-1]='\0';
    else s[i]='\0';
    
    for (i = 0; s[i] != '\0'; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
            count++;
    }
    printf("%i \n", count);
}
