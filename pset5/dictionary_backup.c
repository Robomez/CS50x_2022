// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
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

// TODO: Choose number of buckets in hash table
const unsigned int N = 50625;

// Hash table
node *table[N];

// Function prototypes
void free_nodes(node *ptr);

// Added int to count words hashed into table
unsigned int dict_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Hash function to get to bucket
    int hash_text = hash(word);

    // Cycle through linked list and strcasecmp
    node *tmp = table[hash_text];

    while (tmp != NULL)
    {
        if (strcasecmp(word, tmp->word) == 0)
        {
            return true;
        }
        tmp = tmp->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function

    int j = 0, value = 0;
    while (word[j] != '\0')
    {
        if (word[j] == '\'')
        {
            value += 1;
        }
        else
        {
            value += (toupper(word[j]) - 'A');
        }
        j++;
    }
    return value * j;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
     // TODO
    // Open dictionary file
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("couldn't open dictionary\n");
        return false;
    }

    // Read strings from file one at a time using loop
    // & add to hash table
    // & add 1 to dict_size value (size of hash table)
    char word_read[LENGTH + 1];
    unsigned int hash_dict;

    while (fscanf(dict, "%s", word_read) != EOF)
    {

        // Create a new node for each word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("couldn't malloc space for node\n");
            return false;
        }

        // Hash word to obtain a hash value
        hash_dict = hash(word_read);

        // Insert node into hash table at that location
        strcpy(n->word, word_read);

        if (table[hash_dict] == NULL)
        {
            n->next = NULL;
        }
        else
        {
            n->next = table[hash_dict];
        }
        table[hash_dict] = n;

        // Increment dictionary words counter
        dict_size++;
    }
    fclose(dict);
    printf("dictionary loaded\n");
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // Iterate through hash table looking for lists
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            free_nodes(table[i]);
        }
    }
    return true;
}

// Free list
void free_nodes(node *ptr)
{
    if (ptr->next == NULL)
    {
        free(ptr);
        return;
    }
    else
    {
        free_nodes(ptr->next);
        free(ptr);
    }
}
