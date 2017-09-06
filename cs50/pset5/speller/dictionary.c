/**
 * Implements a dictionary's functionality.
 */
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "dictionary.h"
#include  <string.h> 
#include <ctype.h>
#include <cs50.h>

#define MAX 45

typedef struct node
{
    struct node *next[28];
} node;

node *head;
int number_words=0;
int flag=0;
int count=0;

int chk (const char *word, node * elem)
{
//    eprintf("word=\"%s\" elem=%p\n", word, elem);
    flag=1;
    int word1=0;
    
    if (isupper(*word))
        word1=*word+32-'a'+2;
    if islower(*word)
        word1=*word-'a'+2;
    if (*word==39)
        word1=1;
        
        
    if (elem->next[word1]!=NULL)
    {
        if (*(word)=='\0')
        {
//            eprintf ("*(word+1)==\'\\0\'\n");
            flag=0;
 //           eprintf ("returning %i\n", flag);
            return flag;
        }   
        chk(word+1, elem->next[word1]);
    }
    if (flag==0) { 
//        eprintf ("returning %i\n", flag);
        return flag;
    }
    else { 
//        eprintf ("returning 1\n");
        return 1; 
    }
    

}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
//    eprintf("checking word=%s\n", word);
    flag=0;
    int i=chk(word,head);
    if (i==0 ) return true;
    else return false;
}

void trie (char *c, node * elem)
{
//    eprintf("c=\"%s\" node=%p\n", c, elem);
    node *temp;
    int c1=0;
    c1=*c-'a'+2;
    if (*c==39)
        c1=1;
    
    if (*c!='\0')
    {
        if (elem->next[c1]==NULL){
            elem->next[c1]=malloc (sizeof (struct node));
            
//            eprintf("node created\n");
//            eprintf("c=\"%s\" node=%p\n", c, elem->next[c1]);
            memset(elem->next[c1], 0, sizeof(*elem));
//            temp=elem->next[c1];
//          eprintf("c=\"%s\" node=%p\n", c, temp);
//            trie(c+1, temp);
        }
/*        if (flag==0){
//            head->next[c1]=elem;
//            flag++;
//            trie(c+1, head->next[c1]);
//        }
//        else */
            temp=elem->next[c1];
//            eprintf("c=\"%s\" node=%p\n", c, temp);
            trie(c+1, temp);
    }
    else
    {   
        c1=*c;
//        eprintf("elem=%p\n", elem);
        elem->next[c1]=malloc (sizeof (struct node));
//        elem = elem->next[c1];
//        memset(elem, 0, sizeof(*elem));
    }
}


/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    FILE *dic;
    char word[MAX];
    head = malloc (sizeof (struct node));
    memset(head, 0, sizeof(*head));
    dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
        printf("Could not open %s . \n", dictionary);
        return false;
    }
    while (fscanf(dic,"%s",word)!=EOF)
    {        
//       eprintf("word=%s\n", word);
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
    return 0;
}

void unl(unsigned char pos, node * elem)
{
    
    while ((pos<28) && (elem->next[pos]!=NULL))
    {
        elem=elem->next[pos];
        unl(pos, elem);
        free(elem);
        pos++;
    }
}


/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    unl(0, head);
    return true;
}
