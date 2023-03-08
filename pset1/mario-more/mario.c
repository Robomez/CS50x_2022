    #include <stdio.h>
#include <cs50.h>

int height, sp;

void hash(void);
void row(void);

int main(void)
{
    height = 0;

    // Get height from user and check if it's between 1 and 8
    do
    {
        height = get_int("Height from 1 to 8: ");
    }
    while (height < 1 || height > 8);

    // Rows loop
    sp = height - 1;

    for (int i = 0; i < height; i++)
    {
        row();
        sp--;
        printf("\n");
    }
}

// Print row
void row(void)
{
    // Pyramid of spaces
    for (int j = 0; j < sp; j++)
    {
        printf(" ");
    }
    // # pyramid, two spaces, # pyramid
    hash();
    printf("  ");
    hash();
}

// Print hash pyramid
void hash(void)
{
    for (int j = 0; j < height - sp; j++)
    {
        printf("#");
    }
}