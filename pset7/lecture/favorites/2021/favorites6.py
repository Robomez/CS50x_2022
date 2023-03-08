# Print popularity of titles in CSV, sorted by popularity, using a lampda function

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
# Lambda F is a F wa won't be using later. No need for a name etc.
# key=lambda title: titles[title]
#     lambda <arg to lambda F>: <expression>
for title in sorted(titles, key=lambda title: titles[title], reverse=True):
    print(title, titles[title])