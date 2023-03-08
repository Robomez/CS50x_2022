# Average three numbers using a list and a loop wwith + operator

from cs50 import get_int

# Get scores
scores = []
for i in range(3):
    score = get_int(f"Score {i}: ")
    # Appends a list to the end of list. In this case appended list is only one integer
    scores += [score]

# Print average
average = sum(scores) / len(scores)
print("Average:", average)