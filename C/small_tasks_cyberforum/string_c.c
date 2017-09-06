#include<stdio.h>
#include<string.h>

#define MAX 256

int main (void){
    char s[MAX];
    int i=0, counter=0;
// ввод строки 
    FILE *file = fopen("string.txt", "r");
    if (file != NULL){
        fgets(s,MAX,file);
    }
// подсчет элементов строки     
    for (i=0; s[i]; i++)
        counter++;
    printf("%s \n", s);      // вывод строки 
    printf("%i \n",counter); // вывод количество элементов строки подсчитанной циклом 
    printf("%lu \n",strlen(s)); // вывиод количество элементов строки подсчитанной при помощи ф-ии strlen() из string.h
    fclose(file);
}