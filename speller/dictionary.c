// Implements a dictionary's functionality
#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

int dictionarysize = 0;
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = LENGTH;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    //hash word;
    node *ptr;
    int listno = hash(word);
    //find word
    ptr = table[listno];
    if (ptr == NULL)
    {
        return false;
    }
    while (strcasecmp(ptr->word, word) != 0)
    {
        //printf("%s\n", word);
        ptr = ptr->next;
        if (ptr == NULL)
        {
            return false;
        }
    }
    return true;

}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return strlen(word);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    //open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return 1;
    }
    //read strings one at a time
    char buffer[LENGTH];
    int result = fscanf(file, "%s", buffer);
    //printf("%s\n", buffer);
    int hashno;
    while (result != EOF)
    {
        //printf("%s\n", buffer);
        //make node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("no memory\n");
            return 1;
        }
        strcpy(n->word, buffer);
        //hashword to obtain a hash value
        hashno = hash(buffer);
        //printf("length is %i\n",hashno);
        //insert node into hash table at the location
        n->next = table[hashno];
        table[hashno] = n;

        result = fscanf(file, "%s", buffer);
        dictionarysize++;
    }
    fclose(file);
    return true;

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dictionarysize;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *tmp = NULL;
    node *cursor = NULL;
    for (int i = 0; i < LENGTH; i++)
    {
        cursor = table[i];
        //tmp = table[i];
        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = tmp->next;
            free(tmp);
        }
    }
    return true;
}
