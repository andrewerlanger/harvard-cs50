from cs50 import get_int
import time

# Prompt user for height
while True:
    print("How high would you like your pyramid?")
    height = get_int()
    if height >= 0 and height <= 23:
        break
    else:
        print("Select an integer between 0 and 23, inclusive.\n\n")

# Loop for rows
for i in range(0, height):
    # Print spaces (left)
    print(" " * (height - i - 1), end="")
    # Loop hashes (left)
    print("#" * (i + 1), end="")
    # Space middle
    print(" " * 2, end="")
    # Print hashes (right)
    print("#" * (i + 1), end="")
    # Line-break
    print()