from nltk.tokenize import sent_tokenize

# Initialize two strings, a + b
string_a = "foobar"
string_b = "bar"

# Initialize n
n = 3

# Initialize return list
return_substrings = []

# Calculate string lengths
len_a = len(string_a)
len_b = len(string_b)

# Parse strings into substrings and convert to list
list_a = [string_a[a:a+n] for a in range(len_a - n + 1)]
list_b = [string_b[b:b+n] for b in range(len_b - n + 1)]

print("HERE IS LIST A")
print(list_a)

# Search for matching lines
for a in list_a:
    for b in list_b:
        if a == b:
            return_substrings.append(a)

# Delete duplicates
return_substrings = list(set(return_substrings))

# Print findings
counter = 1
for z in return_substrings:
    print(f"{counter}. \"{z}\"")
    counter += 1
