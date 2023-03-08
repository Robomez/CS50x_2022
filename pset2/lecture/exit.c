#include <stdio.h>
#include <cs50.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Missing command line arg\n");
        return 1;
    }
    // No need for else because if is true it returns 1 and program stops.
    printf("Hello, %s\n", argv[1]);
    return 0;
}