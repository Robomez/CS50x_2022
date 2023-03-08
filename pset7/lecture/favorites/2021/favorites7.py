# Search CSV for popularity of a title

import csv

# Prompt for title
title = input("Title: ").strip().upper()

with open('favorites.csv', 'r') as file:
    reader = csv.DictReader(file)

    # Iterate over CSV file, counting favorites
    counter = 0
    for row in reader:
        if row["title"].strip().upper() == title:
            counter += 1

print(counter)