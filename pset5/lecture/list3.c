// Implement a list of numbers with a linked list

#include <stdio.h>
#include <stdlib.h>

// This struct represents a node
typedef struct node
{
    int number;
    struct node *next;
}
node;

int main(void)
{
    // List of size 0
    node *list = NULL;

    // Add a number to list
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return 1;
    }
    n->number = 1;
    // n->number equals (*n).number
    n->next = NULL;
    list = n;

    // Add second number to list
    // No need to declare a new pointer, pointer n already exists
    n = malloc(sizeof(node));
    if (n == NULL)
    {
        free(list);
        return 1;
    }
    n->number = 2;
    n->next = NULL;
    list->next = n;

    // Add a third number to list
    n = malloc(sizeof(node));
    if (n == NULL)
    {
        // IMPORTANT to free list->next before list, else we'll orphan child nodes
        free(list->next);
        free(list);
        return 1;
    }
    n->number = 3;
    n->next = NULL;
    list->next->next = n;

    // Add a fourth number to list
    n = malloc(sizeof(node));
    if (n == NULL)
    {
        free(list->next->next);
        free(list->next);
        free(list);
        return 1;
    }
    n->number = 4;
    n->next = NULL;
    list->next->next->next = n;

    // Print list
    // Can't use int i as usual. Nodes in LL aren't numbered
    // Never touch list pointer after declaring and initializing. Make a temporary pointer
    for (node *tmp = list; tmp != NULL; tmp = tmp->next)
    {
        printf("%i\n", tmp->number);
    }

    // Free list
    while (list != NULL)
    {
        node *tmp = list->next;
        free(list);
        list = tmp;
    }

    // For loop looks awful. Maybe, there's a better way to write it, but while loop looks pretty OK.
    // for (node *tmp = list->next; tmp != NULL; tmp = list)
    // {
    //     tmp = list->next;
    //     free(list);
    //     list = tmp;
    // }

    return 0;
}
