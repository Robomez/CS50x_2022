// Implicitly casts chars to ints

#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    string s = get_string("String: ");
    for (int i = 0; i < strlen(s); i++)
    {
        // Int and char have the same number.
        // So print with different format code gives different results.
        printf("%c %i\n", s[i], s[i]);
    }
}