# TODO

def main():
    # Check for int and range
    while (True):
        try:
            height = int(input("Height: "))
            if height < 9 and height > 0:
                break
            else:
                print("Not between 1-8")
        except:
            print("Not an int")
    # Print pyramid
    for n in range(1, height + 1):
        print(' ' * (height - n), end='')
        print('#' * n, end='')
        print('  ', end='')
        print('#' * n, end='')
        print()


main()