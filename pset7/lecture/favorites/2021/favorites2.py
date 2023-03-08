# Print unique titles in csv case-sensitively (use set)
from csv import DictReader

titles = set()

with open('favorites.csv', 'r') as file:
    reader = DictReader(file)
    for row in reader:
        titles.add(row["title"])

for title in sorted(titles):
    print(title)