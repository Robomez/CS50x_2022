// Why does it DANGEROUSLY get a string from user?
// Ah, that's because user might type in more than 4 chars in string

#include <stdio.h>

int main(void)
{
    char s[4];
    printf("s: ");
    scanf("%s", s);
    printf("s is: %s\n", s);
}