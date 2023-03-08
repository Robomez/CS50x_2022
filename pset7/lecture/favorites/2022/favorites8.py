# Sort favorites by value using lambda function

import csv

with open('favorites.csv', 'r') as file:
    reader = csv.DictReader(file)

    # Counts dictionary again
    counts = {}

    for row in reader:
        favorite = row['language']

        if favorite in counts:
            counts[favorite] += 1
        else:
            counts[favorite] = 1

for favorite in sorted(counts, key=lambda hippo: counts[hippo], reverse=True):
    print(f'{favorite}: {counts[favorite]}')