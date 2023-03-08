# Count favorites using dictionary

import csv

with open('favorites.csv', 'r') as file:
    reader = csv.DictReader(file)

    # Counts dictionary
    counts = {}

    for row in reader:
        favorite = row['language']
        if favorite in counts:
            counts[favorite] += 1
        else:
            counts[favorite] = 1

for favorite in counts:
    print(f'{favorite}: {counts[favorite]}')