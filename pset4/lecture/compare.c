#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // Get two strings
    char *s = get_string("s: ");
    char *t = get_string("t: ");

    // Compare strings
    if (strcmp(s,t) == 0)
    {
        printf("same\n");
    }
    else
    {
        printf("Different\n");
    }

    printf("\n");
    printf("s %s\n", s);
    printf("s pointer %p\n", s);
    printf("t %s\n", t);
    printf("t pointer %p\n", t);
}