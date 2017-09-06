/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "dictionary.h"

/**
 * Returns true if word is in dictionary else false.
 */

typedef struct node
{
    struct node *next[MAX];
} node;


node *head;
int number_words=0;
int flag=0;
int count=0;

int chk (const unsigned char *word, node * elem)
{
    if (flag == 0) 
    {
        node *elem = malloc(sizeof (struct node));
        elem=head;
        flag++;
    }
    
    if (elem->next[*word]!=NULL)
    {
        if (*(word+1)=='\0')
        {
            flag=0;
            return flag;
        }   
        chk(word+1, elem->next[*word]);
    }
//    else{ printf("false\n"); return 1;}

    if (flag==0) return flag;
    else return 1;
    
}


bool check(const unsigned char *word)
{
    flag=0;
    int i=chk(word,head);
    if (i==0) return true;
    else return false;

}

void trie (unsigned char *c, node * elem)
{
    if (flag==0)
    {
        elem=malloc (sizeof (struct node));
        elem=head;
        flag++;
    }
    if (*c!='\0')
    {
        if (elem->next[*c]==NULL)
            elem->next[*c]=malloc (sizeof (struct node));
        trie(c+1, elem->next[*c]);
    }
    
    else
    {   
        elem->next[*c]=malloc (sizeof (struct node));
        elem = elem->next[*c];
    }
}


/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    FILE *dic;
    unsigned char word[50];
    head = malloc (sizeof (struct node));
    dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
        printf("Could not open %s . \n", dictionary);
        return false;
    }
    while (fscanf(dic,"%s",word)!=EOF)
    {        
        printf("%s \n", word);
        trie (word, head);
        flag=0;
        number_words++;
    }
    fclose (dic);
    return true;
}


/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return number_words;
}

void unl(unsigned char pos, node * elem)
{
    int c=0;
    if (flag==0){
         node *elem = malloc(sizeof (struct node));
        elem=head;
    }
    while (c<MAX)
    {
        if (elem->next[c]!=NULL)
        {
            elem=elem->next[c];
            unl(c, elem);
        }
    free(elem);
    c++;
    flag=0;
    }
}

/**
 * 3Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{

    flag=0;
    unl(0, head);
    
    return true;
}
