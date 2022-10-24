// Implements a dictionary's functionality

// PSEUCODE INSIDE FOLDER
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Global Variables
int word_counter = 0;

// TODO: Choose number of buckets in hash table
const unsigned int N = 1000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hash_index = hash(word);

    for (node *tmp = table[hash_index]; tmp != NULL; tmp = tmp->next)
    {
        if (strcasecmp(word, tmp->word) == 0)
        {
            return true;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int index = 0;

    int iterations = 3;

    for (int i = 0; i < iterations; i++)
    {
        index = index + tolower(word[i]);
    }

    if (index > N)
    {
        index = index % N;
    }

    return index;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Buffer
    char *storage = malloc(LENGTH + 1);

    // Check if no error
    if (storage == NULL)
    {
        return false;
    }

    // Node
    node *n = NULL;

    // Variable that will receive the returned value of the hash function
    int hash_index;

    // Open dictionary file
    FILE *dicionario = fopen(dictionary, "r");

    // Write each string inside the file onto the buffer
    while (fscanf(dicionario, "%s", storage) == 1)
    {

        // One more word to the counter
        word_counter++;

        // Allocate new memory for the n at each iteratio]n
        n = malloc(sizeof(node));

        // Check if no error
        if (n == NULL)
        {
            return false;
        }

        // Copy the content of storage to node->word
        strcpy(n->word, storage);

        // hash_index receives the value returned by the hash(n->word) func
        hash_index = hash(n->word);

        // Check if table[hash_index] is pointing to NULL
        if (table[hash_index] == NULL)
        {
            n->next = NULL;
            table[hash_index] = n;
            continue;
        }

        n->next = table[hash_index];

        table[hash_index] = n;
    }

    fclose(dicionario);

    free(storage);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{

    node *cursor = NULL;

    for (int i = 0; i < N; i++)
    {
        for (node *tmp = table[i]; tmp != NULL; tmp = cursor)
        {
            cursor = table[i]->next;
            free(table[i]);
            table[i] = cursor;
        }
    }

    return true;
}
