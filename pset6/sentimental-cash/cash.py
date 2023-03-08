# TODO
from cs50 import get_float


def main():

    # Get the number of cents
    dollars = 0

    while dollars <= 0:
        dollars = get_float("Number of dollars owed: ")

    cents = int(dollars * 100)

    # Calculate number of quarters
    quarters = calc_quarters(cents)
    cents -= (quarters * 25)

    # Calculate number of dimes
    dimes = calc_dimes(cents)
    cents -= (dimes * 10)

    # Calculate number of nickels
    nickels = calc_nickels(cents)
    cents -= (nickels * 5)

    # Calculate number of pennies
    pennies = cents
    # Return number of pennies
    print("Pennies count", pennies)

    # Sum coins
    coins = quarters + dimes + nickels + pennies

    # Print total number of coins
    print(coins)


def calc_quarters(cents):
    quarters = cents // 25
    print("Quarters count", quarters)
    return quarters


def calc_dimes(n):
    dimes = n // 10
    print("Dimes count", dimes)
    return dimes


def calc_nickels(cents):
    nickels = cents // 5
    print("Nickels count", nickels)
    return nickels


main()