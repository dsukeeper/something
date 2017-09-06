#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main() {
    
    int s[100];                         // в массиве s будут хранится вводимые цифры, если это не цифра тогда будет ноль
    int c, counter=0;                   // counter хранит текущие значение количества цифр в числе
    int max=0, i=0, temp;               // max хранит максимальное кол-во цифр 
    int number=0, number_max=0;         // текущие число и число с максимальным кол-во цифр
    memset(s,0,sizeof(s));              // заполняем массив 0
    while ((c=getchar())!='\n'){
        if (isdigit(c))
            s[i]=c-48;                  // 48 это '0'
        i++;
    }
    for (int j=i; j>0; j--){
        temp=1; 
        counter=0;
        while (s[j]!=0 && j>0){         //выбираем из массива цифры и составляем числа 
            number=number + s[j]*temp;  // значение текущего числа
            temp*=10;
            j--;
            counter++;                  // счетчик цифр в текущем числе
        }
        if (max<counter){               // сравниваем счетчик цифр в текущем числе с максимальным 
            number_max=number;
            max=counter;
        }
        number=0;
    }
    printf("%i", number_max);
}
    

