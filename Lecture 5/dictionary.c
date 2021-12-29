// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    if (table[hash(word)]==NULL) return false;
    node *n = table[hash(word)];
    while(n!=NULL) {
        if (strcasecmp(word,n->word)==0) return true;
        n=n->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    return ((int)toupper(word[0]))-65;
}

// Loads dictionary into memory, returning true if successful, else false
//First malloc should be calloc, the rest malloc?
bool load(const char *dictionary)
{
    // TODO
    char word[LENGTH+1];
    FILE *dicptr = fopen(dictionary,"r");
    if (dicptr==NULL) return false;
    node *n = NULL;
    while (fscanf(dicptr,"%s",word)!=EOF){
        n = malloc(sizeof(node));
        if (n==NULL) return false;
        //Initializing memory must include all parts of the allocated pointer variable. Able to speed up by callocing the first instance, than mallocing the rest (thus not having to assign NULL every time)
        strcpy(n->word,word);
        n->next=NULL;
        if (table[hash(word)] == NULL){
            table[hash(word)] = n;
        } else {
            n->next=table[hash(word)];
            table[hash(word)]=n;
        }
    }
    fclose(dicptr);
    return true;

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    int count=0;
    node *cursor=NULL;
    for (int i=0;i<N;i++){
        cursor = table[i];
        while (cursor!=NULL) {
            count++;
            cursor=cursor->next;
        }
    }

    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *tmp = NULL;
    node *cursor = NULL;
    for (int i=0;i<N;i++){
        cursor = tmp = table[i];
        while (cursor!=NULL){
            cursor=cursor->next;
            free(tmp);
            tmp=cursor;
        }
    }
    return true;
}
//Naive Answer, I could make a hash table and a respectable hash function for AA-ZZ or AAA-ZZZ possibilities thus reducing real time results.