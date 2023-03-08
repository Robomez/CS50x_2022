# Search CSV for popularity of a title using regular expressions

import csv
import re

counter = 0

with open('favorites.csv', 'r') as file:
    reader = csv.DictReader(file)

    # Iterate over CSV file, counting favorites

    for row in reader:
        title = row['title'].strip().upper()
        if re.search("^(THE )?OFFICE$", title):
            counter += 1

print(counter)