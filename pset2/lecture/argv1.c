#include <stdio.h>
#include <cs50.h>

// Prints all command-line argument words one by one
int main(int argc, string argv[])
{
    for (int i = 0; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }
}