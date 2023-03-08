# Write name and number to phonebook without needing to close the file

import csv
from cs50 import get_string

# Get name and number
name = get_string("Name: ")
number = get_string("Number: ")

# Open csv file
with open("phonebook.csv", "a") as file:

    # Print to file
    writets = csv.writer(file)
    writets.writerow([name, number])