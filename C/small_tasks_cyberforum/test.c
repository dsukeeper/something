#include <stdio.h>
#include <string.h>
 
unsigned char DELIM[] = "-+=*/";
 
int main() {
 int counters[256];
 memset(counters,0,sizeof(counters));
 int c;
 while ((c=getchar())!=EOF)
  counters[c]++;
 int sum=0;
 for (int i=0;DELIM[i]; i++)
  sum+=counters[DELIM[i]];
 printf("%d\n", sum);
}