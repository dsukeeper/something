#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

int main (int argc, string argv[]){
    string s,key;
    unsigned int len, len_key, alph;
    int j;
    
    if (argc==1 || argc >2){
        printf("Usage: ./vigenere k");
        return 1;
    }
    key= argv[1];
    len_key=strlen(key);
    for (j=0;j<len_key;j++){
        if (isalpha(key[j])==false) {
            printf("Usage: ./vigenere k");
            return 1;    
        }    
    }
    printf ("plaintext:  ");
    s = get_string();
    len = strlen (s);
    printf("ciphertext: ");
    j=0;
    for(int i=0; i<len; i++){
        int Ci=0;

        int alph_key;
        if (isalpha(s[i])){
            
            if (s[i]>='A' && s[i]<='Z')
                alph = 65;
            else alph = 97;
            
            if (key[j]>='A' && key[j]<='Z')
                alph_key = 65;
            else alph_key = 97;
            

            Ci= ((s[i] - alph)+(key[j]-alph_key))%26 + alph; 
            printf("%c",Ci);
            
            
            if (j==len_key-1)
                j=0;
            else j++;
        } 
        else printf("%c", s[i]);
    }
    printf("\n");
    return 0;
}
    