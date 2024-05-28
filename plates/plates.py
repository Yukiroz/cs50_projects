def main():
    plate = input("Plate: ")
    if is_valid(plate):
        print("Valid")
    else:
        print("Invalid")


def is_valid(s):

    # Check first two is letters DONE

    check1 = True
    for i in s[0:2]:
        if i.isnumeric():
            check1 = False


    # Check len to be between 2 and 6 DONE
    if 1 < len(s) < 7:
        check2 = True
    else:
        check2 = False


    # Numbers cannot be between letters(before letters)

    check3 = True
    found_number = False
    
    for i in s:
        if i.isnumeric():
            found_number = True
        if (found_number == True) and i.isalpha():
            check3 = False


    #first number not 0 DONE

    check4 = True

    for i in s:
        if i.isnumeric():
            if i == "0":
                check4 = False
                #print("0 broke it")
                break
            else:
                break


    # No periods, spaces, or punctuation marks are allowed DONE

    check5 = True

    for i in s:
        if i.isalnum() == False:
            #print("found something bad")
            check5 = False

    # final check DONE

    if check1 and check2 and check3 and check4 and check5:
        return True
    else:
        return False

main()
