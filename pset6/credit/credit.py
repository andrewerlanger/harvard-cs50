from cs50 import get_int

# Prompt user for credit card number
while True:
    print("what's your credit card number?")
    cc_number = get_int()
    if cc_number > 0:
        break
    else:
        print("invalid number. try again.")

# Calculate length of number
length = len(str(cc_number))

# Commit number to list
myList = []
cc_copy = cc_number
for i in range(length):
    myList.append(cc_copy % 10)
    cc_copy = cc_copy // 10

# Calculate sum 1
sum1 = 0
for j in range(1, length, 2):
    temp = 2 * myList[j]
    while temp is not 0:
        sum1 += temp % 10
        temp = temp // 10

# Calculate sum 2
sum2 = 0
for k in range(0, length, 2):
    sum2 += myList[k]

# Calculate sum 3
sum3 = sum1 + sum2

# Calculate first two digits of card number
first_two_digits = (myList[length - 1] * 10) + myList[length - 2]

# Test for cards
valid = True
if (first_two_digits == 34 or
        first_two_digits == 37):
    card = "AMEX"

elif myList[length - 1] == 4:
    card = "VISA"

elif (first_two_digits == 51 or
      first_two_digits == 52 or
      first_two_digits == 53 or
      first_two_digits == 54 or
      first_two_digits == 55):
    card = "MASTERCARD"

else:
    valid = False

if valid == True and sum3 % 10 == 0:
    print("{}" .format(card))

else:
    print("INVALID")