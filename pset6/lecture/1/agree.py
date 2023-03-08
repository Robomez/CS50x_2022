from cs50 import get_string

s = get_string('Do you agree? ')

if s == 'Y' or s == 'y':
    print("Agreed")
elif s == "n" or s == "N":
    print("Not agreed")