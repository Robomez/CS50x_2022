from cs50 import get_string

s = get_string('Do you agree? ').lower()

# If s is in the list of values
if s in ["y", "yes"]:
    print("Agreed")
elif s in ["n", 'no']:
    print("Not agreed")