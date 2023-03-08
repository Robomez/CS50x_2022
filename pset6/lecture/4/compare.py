# Compare two strings

from cs50 import get_string

# Get two strings
s = get_string("s: ")
t = get_string("t: ")

# Compare
if s == t:
    print("Same")
else:
    print("Different")