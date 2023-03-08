# Print all titles in CSV using DictReader

from csv import DictReader

with open('favorites.csv', 'r') as file:
    reader = DictReader(file)

    for row in reader:
        print(row["title"])