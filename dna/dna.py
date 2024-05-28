import csv
import sys
import copy


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")
    # TODO: Read database file into a variable
    data = []
    filename = sys.argv[1]
    with open(filename) as csv_file:
        csv_reader = csv.reader(csv_file)
        for name in csv_reader:
            data.append(name)
    sub = []
    with open(filename) as csv_file:
        reader = csv.reader(csv_file)
        sub = next(reader)
    # print(sub)
    # TODO: Read DNA sequence file into a variable
    seq = sys.argv[2]
    with open(seq, 'r') as txt_file:
        text = txt_file.read().rstrip()
    # TODO: Find longest match of each STR in DNA sequence

    length = len(sub)
    dna = []
    datanoname = []
    datanoname = copy.deepcopy(data)
    # print(data)
    datanoname.pop(0)

    for i in datanoname:
        i.pop(0)
        for index, j in enumerate(i):
            i[index] = int(j)
    # print(datanoname)
    for i in range(1, length):
        # print(sub[i])
        dna.append(longest_match(text, sub[i]))
    # print(dna)
    # TODO: Check database for matching profiles
    found = None
    for index, i in enumerate(datanoname):
        if i == dna:
            # print("found")
            # print("I is:", i)
            found = index + 1
            print(data[found][0])
    if not found:
        print("No match")
    print(datanoname)
    print(dna)

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
