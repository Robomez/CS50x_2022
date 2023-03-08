#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

int main(void)
{
    int i = 0;
    while (true)
    {
        printf("\r%i", i);
        i++;
    }
}