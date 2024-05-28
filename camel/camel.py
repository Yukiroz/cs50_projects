# ask for a camel
camel = input("camelCase: ")

# start copying camel to snake while lowering one letter at a time and if it finds a capital letter, add a "_", then continue copying
for i in camel:
    if i.isupper():
        print("_", end="")
    print (i.lower(), end="")
print("")
