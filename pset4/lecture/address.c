#include <stdio.h>
#include <cs50.h>

int main(void)
{
    char *s = "HI!";

    printf("%c\n", s[0]);
    printf("%p\n", s);

    printf("%c\n", *(s+1));
    printf("%p\n", &s[1]);

    printf("%c\n", s[2]);
    printf("%p\n", &s[2]);

    printf("%c\n", *(s+3));
    printf("%p\n", &s[3]);

}