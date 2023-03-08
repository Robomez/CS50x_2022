// Determines the length of a string

#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    string name = get_string("Name: ");

    int j = 0;
    while (name[j] !='\0')
    {
        j++;
    }
    printf("%i\n", j);
}