# Print unique titles in CSV case-insensitively

import csv

titles = set()

with open('favorites.csv', 'r') as file:
    reader = csv.DictReader(file)

    # Iterate over CSV file, adding each (uppercased) title to set
    for row in reader:
        titles.add(row['title'].strip().upper())

    for title in sorted(titles):
        print(title)