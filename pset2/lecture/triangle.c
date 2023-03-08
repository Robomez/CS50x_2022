// Get 3 real numbers - triange side lengths. Test, if it works out.
#include <stdio.h>
#include <cs50.h>

bool valid_triangle(float s, float array[]);

int main(void)
{
    float sides[3];
    float sum = 0;

    // Get sides (float > 0)
    for (int i = 0; i < 3; i++)
    {
        sides[i] = get_float("Side: ");
        sum += sides[i];
    }
    printf("Sum %.2f\n", sum);

    //test if valid (func valid_triangle)
    bool valid = valid_triangle(sum, sides);
    if (valid == true)
    {
        printf("Triange OK\n");
        return(valid);
    }
    else
    {
        printf("Not a triangle\n");
        return(valid);
    }
}

bool valid_triangle(float s, float array[])
{
    // ckeck if each side is positive & sum of 2 > 3rd
    int c = 0;
    for (int i = 0; i < 3; i++)
    {
        if (array[i] > 0 && s - array[i] > array[i])
        {
            c++;
        }
    }
    printf("Good side count %i\n", c);

    //check if all 3 sides suffice
    if (c == 3)
    {
    return true;
    }
    else
    {
        return false;
    }
}