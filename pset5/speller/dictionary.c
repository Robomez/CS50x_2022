// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table

// TRIE

// Every node contains an array of RANGE(27) node*s a-z + "\'"
// If that node in NULL, then that letter isn't the next letter of any word in that sequence
// Every node indicates whether it's the last character of a word

// TODO: Choose number of buckets in hash table
const int RANGE = 27;

typedef struct node
{
    bool is_word;
    struct node *children[RANGE];
}
node;

// Variables and such
node *head;
node *tmp;
node *new;
unsigned int bucket = 0;
unsigned int dict_size = 0;
int k = 0;

// Functions declaration
node *new_node();
void free_inside(node *node);

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    k = 0;
    tmp = head;

    while (word[k] != '\0')
    {
        // Get bucket number, a-z + '
        if (word[k] == '\'')
        {
            bucket = 26;
        }
        else
        {
            bucket = toupper(word[k]) - 'A';
        }

        // If bucket is empty, means no such word. If full, move tmp to that bucket
        if (tmp->children[bucket] != NULL)
        {
            tmp = tmp->children[bucket];
        }
        else
        {
            return false;
        }
        // Move to next letter
        k++;
    }

    // Got to the last letter. Check tmp if it is_word. Y - word is in dictionary.
    if (tmp->is_word == true)
    {
        return true;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    return false;
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

    // Read letters from file one at a time using loop
    // & add to trie
    // & add 1 to dict_size value (size of hash table)
    char word_read[LENGTH + 1];

    head = new_node();

    while (fscanf(dict, "%s", word_read) == 1)
    {
        tmp = head;

        // Iterate letters
        k = 0;
        while (word_read[k] != '\0')
        {
            // Get bucket number, a-z + '
            if (word_read[k] == '\'')
            {
                bucket = 26;
            }
            else
            {
                bucket = toupper(word_read[k]) - 'A';
            }

            // If bucket is empty, fill. Else point tmp at that bucket
            if (tmp->children[bucket] != NULL)
            {
                tmp = tmp->children[bucket];
            }
            else
            {
                new = new_node();
                tmp->children[bucket] = new;
                tmp = new;
            }

            // Move to next letter
            k++;
        }

        // Last letter gets is_word true'd
        tmp->is_word = true;

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
    free_inside(head);
    return true;
}

void free_inside(node *node)
{
    if (node == NULL)
    {
        return;
    }

    for (k = 0; k < RANGE; k++)
    {
        free_inside(node->children[k]);
    }

    free(node);
    return;
}

node *new_node()
{
    node *n = malloc(sizeof(node));
    n->is_word = false;
    for (int j = 0; j < RANGE; j++)
    {
        n->children[j] = NULL;
    }
    return n;
}