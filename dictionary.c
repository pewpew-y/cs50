// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
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
const unsigned int N = 2381;

// Hash table
node *table[N];
void nullify(void)
{
    for (int k = 0; k < N; k++)
    {
        table[k] = NULL;
    }
}

//keeping count of no. of words in load for size
int counter = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *temp = NULL;
    int i = 0;
    i = hash(word);
    temp = table[i];
    if (temp == NULL)
    {
        return false;
    }
    while (strcasecmp(temp->word, word) != 0)
    {
        if (temp->next == NULL)
        {
            return false;
        }
        temp = temp->next;
    }
    return true;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int total = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        total += tolower(word[i]);
    }
    total = (total << 3);
    return total % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    nullify();
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    char words[LENGTH + 1];
    node *temp = NULL;
    int i = 0;
    while (fscanf(file, "%s", words) != EOF)
    {
        temp = malloc(sizeof(node));
        if (temp == NULL)
        {
            return false;
        }
        strcpy(temp->word, words);
        i = hash(words);
        if (table[i] == NULL)
        {
            temp->next = NULL;
            table[i] = temp;
        }
        else
        {
            temp->next = table[i];
            table[i] = temp;
        }
        counter++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *temp, *cursor;
    temp = cursor = NULL;
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            temp = cursor = table[i];
            while (cursor->next != NULL)
            {
                cursor = cursor->next;
                free(temp);
                temp = cursor;
            }
            free(temp);
        }
    }
    return true;
}
