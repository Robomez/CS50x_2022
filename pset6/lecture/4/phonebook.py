# Saves names and numbers to a csv file

import csv
from cs50 import get_string

# Open a csv file
file = open("phonebook.csv", "a")

# Get name and number
name = get_string("Name: ")
number = get_string("Number: ")

# Print to file
pisaka = csv.writer(file)
pisaka.writerow([name, number])

# Close file
file.close()