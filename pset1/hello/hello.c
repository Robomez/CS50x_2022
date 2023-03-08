#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string answer = get_string("What's your name? ");

    // Check if answer is present
    if (answer[0] == '\0')
    {
        // Print basic answer without name
        printf("Hello, anon! =)\n");
    }
    else
    {
        // Print answer with name
        printf("Hello, %s! =)\n", answer);
    }
}