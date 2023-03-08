# Print popularity of titles in CSV, sorted by title

import csv

# Dictionary for accuomulating and later sorting titles
titles = {}

with open('favorites.csv', 'r') as file:
    reader = csv.DictReader(file)

    # Iterate over CSV, adding each uppercased title to dict
    for row in reader :
        title = row['title'].strip().upper()
        if title in titles:
            titles[title] += 1
        else:
            titles[title] = 1

# Print titles in sorted order
for title in sorted(titles):
    print(title, titles[title])