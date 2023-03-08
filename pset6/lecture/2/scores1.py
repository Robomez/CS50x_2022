# Average three numbers using a list and a loop

from cs50 import get_int

# Get scores
scores = []
for i in range(3):
    score = get_int(f"Score {i}: ")
    scores.append(score)

# Print average
average = sum(scores) / len(scores)
print("Average:", average)