#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    string s = get_string("s: ");

    string t = malloc(strlen(s) + 1);

    for (int i = 0, l = strlen(s); i < l; i++)
    {
        t[i] = s[i];
    }

    if (strlen(t) > 0)
    {
        t[0] = toupper(t[0]);
    }

    printf("\ns: %s\n", s);
    printf("t: %s\n", t);

    free(t);
    return 0;
}
