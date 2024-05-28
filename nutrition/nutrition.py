# table/ dictionary
d = {
    "apple": "130",
    "avocado": "50",
    "banana": "110",
    "cantaloupe": "50",
    "grapefruit": "60",
    "grapes": "90",
    "honeydew Melon": "50",
    "kiwifruit": "90",
    "lemon": "15",
    "lime": "20",
    "nectarine": "60",
    "orange": "80",
    "peach": "60",
    "pear": "100",
    "pineapple": "50",
    "plums": "70",
    "strawberries": "50",
    "sweetcherries": "100",
    "tangerine": "50",
    "watermelon": "80",
}

# input DONE
fruit = input("Item: ")
fruit = str(fruit)
fruit = fruit.replace(" ", "")
if fruit.isalpha() == False:
    print("", end="")
else:
    fruit = fruit.lower()

    if fruit in d:

        # check table for name and output calories
        print(d[fruit])



