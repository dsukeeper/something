#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

int main (int argc, string argv[]){
    string s;
    unsigned int key, len, alph;
    if (argc==1 || argc >2){
        printf("Usage: ./caesar k");
        return 1;
    }
    
    key= atoi(argv[1]);
    printf ("plaintext:  ");
    s = get_string();
    len = strlen (s);
    printf("ciphertext: ");
    for(int i=0; i<len; i++){
        int Ci=0;
        if (isalpha(s[i])){
            
            if (s[i]>='A' && s[i]<='Z')
                alph = 65;
            else alph = 97;
            
            Ci= ((s[i] - alph)+key)%26 + alph; 
            printf("%c",Ci);
        } 
        else printf("%c", s[i]);
    }
    printf("\n");
    return 0;
}
    
