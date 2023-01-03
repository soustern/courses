from cs50 import get_int
from sys import exit
from math import ceil


# Establishing lists
num_odd = []
num_even = []

card_num = get_int("Card number: ")

# Get validated input || The total count of digits in the card number must not be different than 13, 15 or 16
if len(str(card_num)) != 13 and len(str(card_num)) != 15 and len(str(card_num)) != 16:
    print("INVALID")
    exit(1)

# Reseting num_store value to the card number (user input)
num_store = card_num

# Loop to get every digit (odd and even) and store in list
for i in range(ceil(len(str(card_num)) / 2)):

    # Get every other digit and apply the respective logic for odd number
    storage = int((num_store % 100) / 10)

    num_odd.append(storage * 2)

    if num_odd[i] > 9:
        num_odd[i] = int((num_odd[i] % 10) + (num_odd[i] / 10))

    # Get ever remaning digit and apply the respective logic for even number
    storage = int((num_store % 100) % 10)

    num_even.append(storage)

    # Dividing card number by 100 so we get rid of the previous two digits we already processed previously in the loop
    num_store = num_store / 100

print(num_even, num_odd)

# Get the sum of all the digits in both the odd and even lists
sum_of_all = sum(num_odd) + sum(num_even)
print(sum_of_all)

# Making sure the sum of both even and odd number is equal to zero
if sum_of_all % 10 != 0:
    print("INVALID")
    exit(1)

# Checking if total digit size of card number is 15 || that can only mean it is American Express
if len(str(card_num)) == 15:

    # Checking if first two digis of card num is 37 or 34
    if int(str(card_num)[:2]) == 37 or int(str(card_num)[:2]) == 34:
        print("AMEX")
        exit(0)

# Checking if total digit size of card number is 13 or 16 || that can mean it is Visa or Mastercard
if len(str(card_num)) == 13 or len(str(card_num)) == 16:

    # Checking if the last digit of card num 4 || that means it is visa
    if int(str(card_num)[:1]) == 4:
        print("VISA")
        exit(0)

    # checking if the last two digits of card_num is beetween 51 and 55 || That means it is mastercard
    if len(str(card_num)) == 16:

        # Checking if total digit size of card number is 16 || must be this way for Mastercard
        if int(str(card_num)[:2]) > 50 and int(str(card_num)[:2]) < 56:
            print("MASTERCARD")
            exit(0)

print("INVALID")
exit(1)