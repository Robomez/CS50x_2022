#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name = get_string("What's your name? ");
    int age = get_int("What's your age? ");
    string number = get_string("What's your number? ");

    printf("Age is %s, name is %i, phone is %s\n", name, age, number);
}