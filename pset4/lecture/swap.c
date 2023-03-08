// Swap two integers
// Using pointers. Else one F gives only copies of variables to another F

#include <stdio.h>

void swap(int *a, int *b);

int main(void)
{
    int x = 1;
    int y = 2;

    printf("x is %i, y is %i\n", x, y);
    // Send x and y addresses
    swap(&x, &y);
    printf("Now x is %i, y is %i\n", x, y);
}

// Get in pointers to variables
// So in parentheses we declare pointers int *a and int *b. That's why there're stars. Not dereferencing.
void swap (int *a, int *b)
{
    // We put whatever is at location a into temp (dereference a). (value of x in our case)
    int tmp = *a;
    // Whatever is (at location b) put it (at location a). () - dereference.
    // value of y is at loc b. put it in loc a, replace x value.
    *a = *b;
    // Whatever is in temp, put it (at location b). () - dereference
    // value of original x is in temp. replase value of y by value of original x.
    *b = tmp;
}