#include <stdio.h>
#include <string.h>
 
int main() {
 int counters[10];
 int len=0;
 int count=0;
 memset(counters,0,sizeof(counters));
 int c;
 while ((c=getchar())!='\n'){
  counters[c-'0']++;
  len++;
 }
  
 for (int i=0;i<=len; i++){
  if (counters[i]>1)
   count++;
 }
 printf("%i\n", count);
 printf("%i\n", len);
}