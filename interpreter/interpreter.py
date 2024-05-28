calc = input("Expression: ")
x, y, z = calc.split(" ")
x = int(x)
z = int(z)
if y == "+":
    print(float(x + z))
elif y == "-":
    print(float(x - z))
elif y == "*":
    print(float(x * z))
elif y == "/":
    print(x / z)
