 #include <stdio.h>
 #include <cs50.h>

 int main(void)
 {
    // Starting number of llamas not less than 9, bc at 8 integer start/3 = start/2
    int start, end, years = 0;
    do
    {
        start = get_int("How many llamas to start with? Not less than 9 or we won't manage ");
    }
    while (start < 9);

    // How many llamas do we need
    do
    {
        end = get_int("How many llamas do we need? ");
    }
    while (end < start);

    // Substract and add llamas (loop). Every year 1/3 are born and 1/4 pass away
    while (start < end)
    {
        start += (start / 3) - (start / 4);
        // Equal to adding 1/12th
        years++;
    }

    // Print the number of years
    printf("It will take %i years to get there\n", years);
 }