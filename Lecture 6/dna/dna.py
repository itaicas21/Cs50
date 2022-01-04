import csv
import sys


def main():
    # TODO: Check for command-line usage
    if len(sys.argv)!=3 :
        return print ("Incorrect Input")

    # TODO: Read database file into a variable
    people=[]
    with open(sys.argv[1],newline='') as db:
        reader = csv.DictReader(db) # DictReader categorized values by column name,reader by index
        for row in reader: # every columns index is swapped with the value of the first rows values per index
            people.append(row)
    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2],'r') as file:
        sequence = file.read()
    # TODO: Find longest match of each STR in DNA sequence
    person ={}
    for field in people[0]:
        if field=='name':
            continue
        person[field]=0
    for field in person:
        person[field] = longest_match(sequence,field)

    # TODO: Check database for matching profiles
    for i in range(len(people)):
        flag=True
        for field in people[i]:
            if field == 'name':
                continue
            if int(people[i][field])!=int(person[field]):
                flag=False
        if flag==True:
            return print(people[i]["name"])
    return print("No match")


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
