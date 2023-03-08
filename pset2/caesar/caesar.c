#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

bool only_digits(string arg);
char rotate(char a, int rot);

int main(int argc, string argv[])
{
    // If there's no command-line argument or more than 1 command-line argument, print "Usage: ./caesar key" and return main value 1.
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // If char in command-line argument is not decimal digit, print message "Usage: ./caesar key" and return main value 1.
    if (only_digits(argv[1]) == false)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Convert argv[1] from string to int
    int key = atoi(argv[1]);

    // Output "plaintext:  " and prompt the user for a string using get_string
    string plaintext = get_string("plaintext:  ");

    // For each char in plaintext
    string ciphertext = plaintext;
    for (int i = 0, l = strlen(plaintext); i < l; i++)
    {
        char a = rotate(plaintext[i], key);
        ciphertext[i] = a;
    }

    // Output result
    printf("ciphertext: ");
    printf("%s\n", ciphertext);
    return 0;
}

bool only_digits(string arg)
{
    int l = strlen(arg);
    for (int i = 0; i < l; i++)
    {
        if (isdigit(arg[i]) == 0)
        {
            return false;
        }
    }
    return true;
}

char rotate(char a, int rot)
{
    // Rotate char using key
    if (isalpha(a))
    {
        if (isupper(a))
        {
            // Capitalized stay caps,
            a = (a - 65 + rot) % 26 + 65;
        }
        else
        {
            // Lowercase stay lower.
            a = (a - 97 + rot) % 26 + 97;
        }
    }
    return a;
}