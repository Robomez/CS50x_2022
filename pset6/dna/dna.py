import csv
import sys


def main():

    # TODO: Check for command-line usage
    # Argv[1] is database csv. Argv[2] is a sequence txt file.
    # If number of args is incorrect, print an error msg with ptint()
    if len(sys.argv) != 3:
        print("Usage: dna.py 'database filename' 'sequence filename'")
        exit(1)

    # TODO: Read database file into a variable
    # First row of CSV - column names. Its forst col is word 'name', remaining cols are STR seqs themselves
    people = []
    with open(sys.argv[1], "r") as file:
        # Get persons dictionaries
        reader = csv.reader(file)
        for person in reader:
            people.append(person)

    with open(sys.argv[1], "r") as file:
        # Get STR list
        STRs = file.readline().strip('\n').split(sep=',')
        STRs.pop(0)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as file:
        reader = file.read()
        sequence = reader

    # TODO: Find longest match of each STR in DNA sequence
    # STR_list for longest STR runs
    STR_list = []
    for i in range(len(STRs)):
        STR_count = longest_match(sequence, STRs[i])
        # Store them in a dict or list
        STR_list.append(STR_count)

    # TODO: Check database for matching profiles
    match_count = 0
    # every row(person) in people
    for j in range(1, len(people)):
        STR_comp = []
        # Every value in person add to temp list STR_comp
        for i in range(1, len(person)):
            STR_comp.append(int(people[j][i]))
        # If it's an exact match, print the name of the matching individual
        if STR_comp == STR_list:
            print(people[j][0])
            match_count += 1
    # If no match found, print "No match"
    if match_count == 0:
        print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
