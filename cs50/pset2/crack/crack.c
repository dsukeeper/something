#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>


#define _GNU_SOURCE
#include <crypt.h>

int main (int argc, string argv[]){
    
    string s, hash_pass;
    if (argc==1 || argc >2){
        return 1;
    }
    
    hash_pass=argv[1];
    s = get_string();
    printf("%s",crypt(s,"50"));
}
    
    
    