#include <stdio.h>
#define MAX 100 // максимальное кол-во элементов в строке
int main() {
    
    int s[MAX];
    int i_start=0, i_end=MAX, i=0, flag=0, counter=0;
    int c;
    
    while ((c=getchar())!='\n'){  // вводим строку и сохраняем её в массив s
        
        if (c=='c')              // если находим символ с увеличиваем счетчик
            counter++;
        if (counter==1 && flag==0){ // опеределяем первое ли это вхождение, flag нужен для того чтобы условие сработало один раз
            i_start=i+1;
            flag++;
        }
        if (counter==2 && flag==1){ // если нашли второй символ определяем конец 
            i_end=i-1;
            flag++;
        }
        s[i]=c;
        i++;
    }
    for(i=i_start; i<=i_end; i++) // выводим подстроку - между символами 
        printf("%c",s[i]);
}