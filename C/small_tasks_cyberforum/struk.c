#include<stdio.h>
#include<stdlib.h>
typedef struct student{
    char name[30];
    int day;
    int month;
    int year;
    struct student *next;
} student;

#define TRUE 1

int num=0;

void add_new(student *list){
    struct student *elem=malloc(sizeof(struct student));
    printf("enter students name: ");
    scanf("%s \n", elem->name);
    printf("enter students day of birthday: ");
    scanf("%i \n", &elem->day);
    printf("enter students month of birthday: ");
    scanf("%i \n", &elem->month);
    printf("enter students year of birthday: ");
    scanf("%i \n", &elem->year);
    num++;
    list=elem;
    list->next=malloc(sizeof(struct student));
    list->next=NULL;
    free(elem);
}

void find (student *list){
    if (list!=NULL){
        if (list->day==15)
            printf ("%s", list->name);
        list=list->next;
        find(list);
    }
}

int main() {
    int c;
    student *st = malloc(sizeof(struct student));
    student *head = malloc(sizeof(struct student));
    head=st;
    while (TRUE){
        printf("Enter: \n");
        printf("1 for add a new student \n");
        printf("2 to find people \n ");
        printf("3 for exit\n");
        c=getchar();
            if (c== '1') add_new(st); 
            if (c== '2') find(head);
        
    }
    
}