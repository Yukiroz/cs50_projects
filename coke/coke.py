price = 50



while price > 0:
    print("Amount Due:", + price)
    coin = int(input("Insert Coin: "))
    if (coin == 25) or (coin == 10) or (coin == 5):
        price = price - coin
print("Change Owed:", + (-price) )
