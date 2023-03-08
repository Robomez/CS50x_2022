from cs50 import get_int

# Prompt user for points
points = get_int("How many points? ")

# Compare points
if points < 2:
    print("Fewer than me.")
elif points > 2:
    print("More than me.")
else:
    print("Equal.")