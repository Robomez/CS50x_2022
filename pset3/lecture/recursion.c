// Make pyramid using recursion
#include <stdio.h>
#include <cs50.h>

void draw(int n);

int main(void)
{
    int height = get_int("Height: ");

    draw(height);
}

void draw(int n)
{
    // If nothing to draw. IMPORTANT
    if (n <= 0)
    {
        return;
    }

    draw(n-1);

    // Draw one row of width n
    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
    printf("\n");
}