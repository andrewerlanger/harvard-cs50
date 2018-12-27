from collections import Counter


def call_counter(func):
    def helper(*args, **kwargs):
        helper.calls += 1
        key = str(args) + str(kwargs)
        helper.c[key] += 1
        return func(*args, **kwargs)
    helper.c = Counter()
    helper.calls = 0
    helper.__name__ = func.__name__
    return helper


@call_counter
def min_calc(D, I, S):

    if D[0] <= I[0] and D[0] <= S[0]:
        return (D[0] + 1, 'D')

    elif I[0] <= S[0]:
        return (I[0] + 1, 'I')

    else:
        return (S[0] + 1, 'S')


# Initialize stings a + b
a = "harvard"
b = "yale"

# Append "Ø" to start of each string
a = "0" + a
b = "0" + b

# Calculate length of a + b
length_a = len(a)
length_b = len(b)

# Declare matrix array + fill [0][0]
matrix = [[None, None] * length_b for i in range(length_a)]
matrix[0][0] = (0, None)

# Fill first row
for i in range(1, length_a):
    matrix[i][0] = (i, 'I')

# Fill first column
for j in range(1, length_b):
    matrix[0][j] = (j, 'D')

# For loop for a values
for j in range(1, length_b):

    # For loop for b values
    for i in range(1, length_a):

        # If values are the same
        if a[i] == b[j]:
            matrix[i][j] = (matrix[i - 1][j - 1][0], None)

        # If values are not the same
        else:
            matrix[i][j] = min_calc(matrix[i - 1][j], matrix[i][j - 1], matrix[i - 1][j - 1])

print(f"total distance = {matrix[length_a - 1][length_b - 1][0]}")
print("min_calc was called " + str(min_calc.calls) + " times!")
print(min_calc.c.most_common())