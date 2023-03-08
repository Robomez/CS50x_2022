# Favorite problem instead of favoriite language. Get problem from uset and print its popularity

import csv

with open('favorites.csv', 'r') as file:
    reader = csv.DictReader(file)

    # Counts dictionary again
    counts = {}

    for row in reader:
        favorite = row['problem']

        if favorite in counts:
            counts[favorite] += 1
        else:
            counts[favorite] = 1

favorite = input("Problem: ")
if favorite in counts:
    print(f'{favorite}: {counts[favorite]}')
else:
    print('No problem match found')

# favorite is row['problem'].
# So key probo is argument to it. Doesn't matter it's name. Quantity matters.
# But expression is important. It gets what we send in. Here we send favorite(i.e. row['problem']).
# And it gets counts[favorite], that is counts for a specific problem
# for favorite in sorted(counts, key=lambda probo: counts[probo], reverse=True):
#     print(f'{favorite}: {counts[favorite]}')