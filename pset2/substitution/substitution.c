#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool only_alpha(string arg);
bool not_repeated_chars(string arg);
char substitute(char a, string key);

int main(int argc, string argv[])
{
    // If no command-line argument or more than 1 command-line argument, return main value 1.
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    int l = strlen(argv[1]);
    string key = argv[1];

    // "Key must contain 26 characters."
    if (l != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // "Key must only contain alphabetic characters."
    if (only_alpha(key) == false)
    {
        printf("Key must only contain alphabetic characters.\n");
        return 1;
    }

    // "Key must not contain repeated characters"
    if (not_repeated_chars(key) == false)
    {
        printf("Key must not contain repeated characters.\n");
        return 1;
    }

    // Key is case-insensitive
    for (int i = 0; i < l; i++)
    {
        key[i] = toupper(key[i]);
    }

    // Output "plaintext:  " and prompt the user for a string using get_string
    string plaintext = get_string("plaintext:  ");

    // For each char in plaintext substitute
    string ciphertext = plaintext;
    for (int i = 0, j = strlen(ciphertext); i < j; i++)
    {
        char a = substitute(ciphertext[i], key);
        ciphertext[i] = a;
    }

    // Output result
    printf("ciphertext: ");
    // Print ciphertext
    printf("%s\n", ciphertext);
    return 0;
}

// Only alphabetic
bool only_alpha(string arg)
{
    int l = strlen(arg);
    for (int i = 0; i < l; i++)
    {
        if (isalpha(arg[i]) == 0)
        {
            return false;
        }
    }
    return true;
}

// No repetition of chars
bool not_repeated_chars(string arg)
{
    int l = strlen(arg);
    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (arg[j] == arg[i])
            {
                return false;
            }
        }
        for (int j = i + 1; j < l; j++)
        {
            if (arg[j] == arg[i])
            {
                return false;
            }
        }
    }
    return true;
}

// Cipher each letter
char substitute(char a, string key)
{
    if (isalpha(a))
    {
        // Uppercase returns uppercase
        if (isupper(a))
        {
            a = key[a - 65];
        }
        // lowercase returns uppercase
        else
        {
            a = tolower(key[a - 97]);
        }
    }
    // Non-alphabetic remain unchanged
    return a;
}