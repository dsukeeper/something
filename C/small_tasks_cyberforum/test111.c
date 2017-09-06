#include <stdio.h>
#include <string.h>

int main (void){
    int i=0;
    int len=0; // длинна числа
    int count =0; // кол-во повторяющихся символов
    int counters[20];
    memset(counters,0,sizeof(counters));
    int c;
    while ((c=getchar())!='\n'){
        counters[i]=c-'0';
        i++;
    }
    len = i;    
    counters[i]=10;
    
    for (i=0; i<=len; i++){
        for (int j=i+1; j<=len; j++){
            if (counters[i]==counters[j])
                count++;
        }
    }
    printf("длинна числа %i \n", len);
    printf("количество повторяющихся символов %i \n", count);
}
