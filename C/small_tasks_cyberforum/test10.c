#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main() {
    
    int s[100];                         // в массиве s будут хранится вводимые цифры, если это не цифра тогда будет ноль
    int c, counter=0;                   // counter хранит текущие значение количества цифр в числе
    int min, i=0;                     // min хранит минимальное кол-во цифр 
    memset(s,-1,sizeof(s));              // заполняем массив -1
    while ((c=getchar())!='\n'){
        if (isdigit(c))
            s[i]=c-48;                  // 48 это '0'
        if (c==45)
            s[i]=45;
        i++;
    }
    int i_start, i_end, m_start, m_end; // в данных значениях хранятся индексы массива с текущим числом и максимальным числом
    min=100;
    for (int j=i; j>0; j--){
        counter=0;
        i_start=j;
        while (s[j]>=0 && j>0){         
            j--;
            counter++;                  // счетчик цифр в текущем числе
        }
        i_end=j+1;
        if (s[i_end]==45)
            counter--;
        if (min>counter && counter!=0){               // сравниваем счетчик цифр в текущем числе с минимальным 
            m_start=i_start; 
            m_end=i_end;
            min=counter;
        }
    }
    if (s[m_end]==45){
        printf("%c", s[m_end]);
        m_end++;
    }
    for (i=m_end; i<=m_start; i++){
        printf("%i", s[i]);
    }
}
    

