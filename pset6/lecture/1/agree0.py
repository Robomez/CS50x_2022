from cs50 import get_string

s = get_string("Do you agree? ")

if s == 'y' or s == 'Y':
    print('Agreed')
elif s == 'n' or s == 'N':
    print('Not agreed')