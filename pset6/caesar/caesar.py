import sys
from cs50 import get_string

# Initialize argc
argc = len(sys.argv)

# Check only two things were imported
if argc != 2:
    print("correct usage ./caesar k")
    quit(1)

# Initialize k as int
k = int(sys.argv[1])

# Prompt user for string
print("plaintext: ", end="")
plaintext = get_string()

# Calculate string length
string_length = len(plaintext)

# Convert + print
print("ciphertext: ", end="")
for i in range(string_length):
    # For upper-case
    if plaintext[i].isupper() == True:
        upper = chr(((ord(plaintext[i]) - 65 + k) % 26) + 65)
        print("{}" .format(upper), end="")
    # For lower-case
    elif plaintext[i].islower() == True:
        lower = chr(((ord(plaintext[i]) - 97 + k) % 26) + 97)
        print("{}" .format(lower), end="")
    # For all other cases
    else:
        print("{}" .format(plaintext[i]), end="")

# One last line-break
print()