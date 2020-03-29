import cs50

while True:
    change = cs50.get_float("How many dollars in change would you like?")
    if change <= 0:
        break
    else:
        change = round(change*100)
        coin_type = [25, 10, 5, 1]
        coins = 0
        diff = change

        #loop to loop through types of coins and add up how many coins go into the remaining change
        for coin in coin_type:
            if diff%coin != diff:
                number_of_coins = (diff-(diff%coin))/coin
                coins += number_of_coins
                diff = diff%coin

        #printing minimum number of coins it would take in change
        print(coins)

