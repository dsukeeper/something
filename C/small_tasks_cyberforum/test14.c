/*Написать функцию, которая будет полуать показатель на рядок 
и выполнять удаление всех елементов а из него*/
#include <stdio.h>
#include <string.h>

void f(char *s);

int main()
{
    char str[] = "4a8ydhaha";
    printf ("%s\n", str);
    f(str);
    printf ("%s\n", str);
    return 0;
}

void f(char *s)
{
    int n=strlen(s);
    char str_temp[n];
    for(int i=0, j=0;i<n;i++)
    {
        if (*(s+i) != 'a')
        {
            str_temp[j]=s[i];
            j++;
        }
    }
    strcpy(s, str_temp);
}