# Count number of students with language

import csv

# Number of students:
languages = {
    "C": 0,
    "Scratch": 0,
    "Python": 0
}

# Count votes
with open("languages.csv", "r") as file:
    reader = csv.reader(file)
    next(reader)
    for row in reader:
        langua = row[1]
        languages[langua] += 1

# Print counts
for langua in languages:
    print(f"{langua}: {languages[langua]}")