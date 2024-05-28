# TODO
from cs50 import get_int
import sys
import math


def main():
    # Get int and check if its valid
    while (True):
        creditcardnumber = get_int("Number: ")
        digits = len(str(creditcardnumber))
        if digits == 13 or digits == 15 or digits == 16:
            break
        else:
            print("INVALID")
            sys.exit()

    # Luhn's Algorithm
    checksum = luhn(creditcardnumber)

    table4 = [3]
    table4 = list(str(checksum))

    # print(table4)

    check = table4[(len(table4) - 1)]

    # print(check)

    one = 0
    two = 0

    table3 = [digits]
    table3 = list(str(creditcardnumber))

    one = int(table3[0])
    int(one)
    two = table3[0] + table3[1]
    int(two)

    # print(one)
    # print(two)
    # print(digits)

    if (digits == 13 or 16) and (one == 4) and (check == "0"):
        print("VISA")
    elif (digits == 15) and (two == '34' or two == '37') and (check == "0"):
        print("AMEX")
    elif (digits == 16) and (two == '51' or two == '52' or two == '53' or two == '54' or two == '55') and (check == "0"):
        print("MASTERCARD")
    else:
        print("INVALID")


def luhn(number):
    digits = len(str(number))
    table1 = [digits]
    table2 = [digits]
    temp = []
    total = 0
    table1 = list(str(number))
    table1.reverse()
    table2 = list(str(number))
    table2.reverse()
    for i in range(digits):
        if (i % 2 == 0):
            table1[i] = 0
        if (i % 2 != 0):
            table1[i] = int(table1[i]) * 2
    for i in range(digits):
        if (int(table1[i]) > 9):
            temp = list(str(table1[i]))
            table1[i] = int(temp[0]) + int(temp[1])
    for i in range(digits):
        if (i % 2 != 0):
            table2[i] = 0
    for i in range(digits):
        total = int(total) + int(table1[i]) + int(table2[i])
    # print(table1)
    # print(table2)
    # print(total)
    return total


# Call Main
main()