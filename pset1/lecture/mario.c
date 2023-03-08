#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n;
    while (true)
    {
        n = get_int("Size: ");
        if (n > 1)
        {
            break;
        }
    }

    // For each row (n times)
    for (int i = 0; i < n; i++)
    {
        // For every column (n times)
        for (int j = 0; j < n; j++)
        {
            // Print a brick
            printf("#");
        }
        // Move to other row (for each row as well, outside column loop)
        printf("\n");
    }
}