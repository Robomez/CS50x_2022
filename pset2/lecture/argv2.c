#include <stdio.h>
#include <cs50.h>
#include <string.h>

// Prints characters in an array of strings
int main(int argc, string argv[])
{
    for (int i = 0; i < argc; i++)
    {
        for (int j = 0, n = strlen(argv[i]); j < n; j++)
        {
            // Letter number j from argument number i
            printf("%c\n", argv[i][j]);
        }
        printf("\n");
    }
}