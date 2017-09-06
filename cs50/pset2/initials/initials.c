#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>


int main (void){
    string name;
    int len;
    bool look_error;
    do{
        look_error = false;
        name = get_string();
        len = strlen (name);
        for (int i=0; i<len; i++){
            if (isalpha(name[i]))
                look_error = false;
            else 
            { 
                if (name[i]==' ')
                    look_error = false;
                else {
                    look_error = true;
                    break;
                }
            }
                
        }
    }
    while (look_error);
    

    for (int i=0; i<len;i++){
       if (name[i]!=' '){
           printf("%c", toupper(name[i]));
           do{
               i++;
           }while ((name [i]!=' ') && (i!=len));    
       }
   }
   printf("\n");
    

}   