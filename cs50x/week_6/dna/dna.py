import csv
from sys import exit, argv
import re

# Program tha receives two files, one database.csv for profiles with their respective DNA signatures
# And one whole DNA signature.txt
# The goal is to check for a DNA signature match a print out the result

def main():

    # Check user input
    if len(argv) != 3:
        print("Usage: python dna.py 'file.csv' 'file.txt'")
        exit(1)

    # Read database file into a variable
    database = []
    with open(argv[1], "r") as file:
        storage = csv.DictReader(file)
        for row in storage:
            database.append(row)

    # Read DNA sequence file into a variable
    sequence = []
    with open(argv[2], "r") as file:
        sequence = file.read().rstrip()

    # Define list with all the possible sequences
    # Define one for a small sequence
    # Define one for a large sequence
    dna_large = ["AGATC", "TTTTTTCT", "AATG",
                 "TCTAG", "GATA", "TATC", "GAAA", "TCTG"]
    dna_small = ["AGATC", "AATG", "TATC"]

    # Define a storage list
    sequence_count = []

    # Check for small database
    if "small" in argv[1]:

        # Find longest match of each STR in DNA sequence
        for i in dna_small:
            sequence_count.append({i: longest_match(sequence, i)})

        # Check database for matching profiles
        for i in range(len(database)):

            # Define a variable that will increment the amount of times the dna signatures match
            increment = 0

            # Check for each STR present in the selected DNA sequence
            for j in range(len(dna_small)):

                # Check for that key and that value at that iteration
                # For each match, increment += 1
                if int(database[i][str(dna_small[j])]) == int(sequence_count[j][str(dna_small[j])]):
                    increment += 1

                # If increment reach a amount respective to the selected list, there is a match
                if increment == 3:
                    print(database[i]['name'])
                    exit(0)

    # Check for large database
    if "large" in argv[1]:

        # Find longest match of each STR in DNA sequence
        for i in dna_large:
            sequence_count.append({i: longest_match(sequence, i)})

        # Check database for matching profiles
        # Check for each profile at the database
        for i in range(len(database)):

            # Define a variable that will increment the amount of times the dna signatures match
            increment = 0

            # Check for each STR present in the selected DNA sequence
            for j in range(len(dna_large)):

                # Check for that key and that value at that iteration
                if int(database[i][str(dna_large[j])]) == int(sequence_count[j][str(dna_large[j])]):
                    # For each match, increment += 1
                    increment += 1

                # If increment reach a amount respective to the selected list, there is a match
                if increment == 8:
                    print(database[i]['name'])
                    exit(0)

    print("No match")
    exit(0)


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
