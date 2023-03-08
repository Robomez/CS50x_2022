#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt user for x
    float x = get_int("x: ");

    // Prompt user for y
    float y = get_int("y: ");

    // Perform addition
    long z = x + y;
    printf("x+y= %li\n", z);

    //Pervorm division
    float zz = x / y;
    printf("x/y= %.50f\n", zz);

    if (x < y)
    {
        printf("x is less than y\n");
    }
    else if (x > y)
    {
        printf("x is bigger than y\n");
    }
    else
    {
        printf("x is equal to y\n");
    }
}
