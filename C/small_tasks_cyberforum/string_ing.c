#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<string.h>

void str_ing (char s[]);

int main (void){
    char s[]="testing a program with ing\0";
    printf ("%s \n", s);
    str_ing(s);

    printf ("%s \n", s);
}

void str_ing (char s[]){
    int count=0, i=0, count_ing=0;
    int len = strlen(s);
    do {
        while (isalpha(s[i]) && s[i]!=' '){
            count++;
            i++;
        }
        if (count >= 3)
            for (int j=i-3;j<i;j++)
                if (s[j]=='i'|| s[j]=='n' || s[j]=='g') 
                    count_ing++;
        
        if (count_ing==3){
            for (int j=i;j>i-1-count;j--)
                s[j]='\b';
        }
        count=0;
        count_ing=0;
        i++;
    }while (i<len);
    int j;
    for (i=0,j=0;i<len; i++)
        if (s[i]!='\b'){
            s[j]=s[i];
            j++;
        }
    s[j]='\0';
    
}