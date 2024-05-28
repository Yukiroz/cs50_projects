while True:

    # get fraction
    fraction = input("Fraction: ")

    # split fraction into value 1, /, value 2

    try:
        x, y = fraction.split('/')
        x = int(x)
        y = int(y)
        # make fraction into %
        fuel = round((x*100)/y)
    except ZeroDivisionError:
        print("", end="")
    except ValueError:
        print("", end="")
    else:
        # check fuel
        if fuel >= 0 and fuel <= 100:
            break

# print E, % or F
if fuel <= 1:
    print("E")
elif fuel >= 99:
    print("F")
else:
    print(fuel,"%", sep="")



