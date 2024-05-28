Input = input("Input: ")
#print("Output: ", end="")
for i in Input:
    l = i.lower()
    if (l!="a") and (l!="e") and (l!="i") and (l!="o") and (l!="u"):
        print(i, end="")
print()
