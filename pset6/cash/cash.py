from cs50 import get_int, get_float

# Initialize change + coins variables
change = -1.00
coins = 0

# Prompt user for change value
while change <= 0:
    change = get_float("how much change is owed?\n")

# Convert change to int
change = round(change * 100)
print("{}" .format(change))

# Calculate number of 25c coins
while change >= 25:
    change -= 25
    coins += 1

# Calculate number of 10c coins
while change >= 10:
    change -= 10
    coins += 1

# Calculate number of 5c coins
while change >= 5:
    change -= 5
    coins += 1

# Calculate number of 1c coins
while change >= 1:
    change -= 1
    coins += 1

print("{}" .format(coins))