#include<stdio.h>
#include<stdlib.h>
typedef struct first{
    int count;
    struct first *next;
} first;

int main(){
    int N=10;
    first *elem = malloc (sizeof (struct first));
    first *head = malloc (sizeof (struct first));
    head=elem;
    for (int i=0;i<N;i++){
        elem->count=i;
        if (i==N-1)
            elem->next=NULL;
        else
            elem->next=malloc (sizeof (struct first));
        printf("%i \n",elem->count);
        elem=elem->next;
    }
    while(head!=NULL){
        printf("%i \n",head->count);
        head=head->next;

    }
    while(head!=NULL){
        head=head->next;
        free(head);
    }
    free(head);
    free(elem);

}