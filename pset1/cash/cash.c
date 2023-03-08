#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

int get_cents(void)
{
    // Prompt user for a number. Not negative, not word.
    int cents;
    do
    {
        cents = get_int("Number of cents owed: ");
    }
    while (cents < 1);
    printf("Cents amount %i\n", cents);
    return cents;
}

int calculate_quarters(int cents)
{
    // TODO
    int quarters = cents / 25;
    printf("Quarters count %i\n", quarters);
    return quarters;
}

int calculate_dimes(int cents)
{
    // TODO
    int dimes = cents / 10;
    printf("Dimes count %i\n", dimes);
    return dimes;
}

int calculate_nickels(int cents)
{
    // TODO
    int nickels = cents / 5;
    printf("Nickels count %i\n", nickels);
    return nickels;
}

int calculate_pennies(int cents)
{
    // TODO
    int pennies = cents / 1;
    printf("Pennies count %i\n", pennies);
    return pennies;
}
