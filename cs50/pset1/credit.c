#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main (void){
    string card, namecard;
    int digits[16];
    int len, invalid=0;
    int sum=0;
    
    do {
        invalid=0;
        printf("Number:");
        card = GetString();
        len = strlen(card);
        for (int i=0; i<len; i++){
            if ((card[i]<'0') || (card [i]>'9'))
                invalid=1;
        }

    }
    while (invalid==1);
    

        if ((len<13) || (len>16))
            printf("INVALID\n");
        else{
    
        for (int i=0; i<len; i++)
            digits[i]=(card[i]-'0');
        
        if((digits[0]==3 && (digits[1]==4 || digits[1]==7)) && (len == 15)){
                namecard="AMEX";
        }
            
        if((digits[0]==5 && (digits[1]>0 && digits[1]<6)) && (len == 16)){
                namecard="MASTERCARD";
        }
        
        if((digits[0]==4) && (len == 13 || len==16)) {
                namecard="VISA";
        }
            
        for (int i=len-1; i<0;i=i-2){
            if (digits[i]>=5)
                sum=sum+(digits[i]*2-10)+1;
            else sum=sum+digits[i]*2;
        }
        
        for(int i=len; i<0; i=i-2)
            sum=sum+digits[i];
                        
        if ((sum%10)==0)
            printf("%s\n",namecard);
        else printf("INVALID\n");
        }    
}