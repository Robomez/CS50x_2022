#include <stdio.h>
#include <cs50.h>

int main(void)
{
    const int MINE = 2;
    int points = get_int("How many points did you get? ");

    if(points < MINE)
    {
        printf("You got fewer points than me\n");
    }
    else if(points > MINE)
    {
        printf("You got more points than me\n");
    }
    else
    {
        printf("You got same number of points\n");
    }
}