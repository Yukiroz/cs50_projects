def main():
    hour = input("What time is it? ")
    hour = convert(hour)

    if 7 <= hour <= 8:
        print("breakfast time")
    elif 12 <= hour <= 13:
        print("lunch time")
    elif 18 <= hour <= 19:
        print("dinner time")


def convert(time):
    if ("a.m.") in time:
        # split and remove am
        x, y = time.split(" ")
        x, y = x.split(":")
    elif ("p.m.") in time:
        # split and remove pm
        x, y = time.split(" ")
        x, y = x.split(":")
        x = int(x)
        x = x + 12
    else:
        x, y = time.split(":")
    x = int(x)
    y = int(y)
    y = y / 60
    #print(x)
    #print(y)
    word = x + y
    #print(word)
    return word


if __name__ == "__main__":
    main()
