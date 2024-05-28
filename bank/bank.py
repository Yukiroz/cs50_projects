greeting = input("Greeting: ").strip()
Hello = greeting.startswith("Hello")
H = greeting.startswith("H")
if Hello:
    print("$0")
elif H:
    print("$20")
else:
    print("$100")
