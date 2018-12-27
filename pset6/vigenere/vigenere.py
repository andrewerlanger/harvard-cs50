from cs50 import get_string
import sys

# Check program took one command-line argument
if len(sys.argv) != 2:
    print("usage: ./vigenere keyword")
    quit(1)

# Commit keyword to string k
k = sys.argv[1]

# Check keyword is all alphabetical characters + convert to lower-case
if k.isalpha() != True:
    print("usage: ./vigenere keyword")
    quit(1)
else:
    k = k.lower()

# Prompt user for plaintext
print("plaintext: ", end="")
plaintext = get_string()

# Convert + print
pos = 0
k_length = len(k)
p_length = len(plaintext)
print("ciphertext: ", end="")

for j in range(p_length):
    if plaintext[j].isupper() == True:
        upper_shift = ((ord(plaintext[j]) - 65) + (ord(k[pos % k_length]) - 97)) % 26
        print("{}" .format(chr(upper_shift + 65)), end="")
        pos += 1
    elif plaintext[j].islower() == True:
        lower_shift = ((ord(plaintext[j]) - 97) + (ord(k[pos % k_length]) - 97)) % 26
        print("{}" .format(chr(lower_shift + 97)), end="")
        pos += 1
    else:
        print("{}" .format(plaintext[j]), end="")

print()