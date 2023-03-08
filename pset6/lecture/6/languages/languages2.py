import csv

# Number of peopole who prefer some problem
languages = {
    "Scratch": 0,
    "C": 0,
    "Python": 0
}

# Count votes
with open("languages.csv", "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        langa = row["language"]
        languages[langa] += 1

for langa in languages:
    count = languages[langa]
    print(f"{langa}: {count}")