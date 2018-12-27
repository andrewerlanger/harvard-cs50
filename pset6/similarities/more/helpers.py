from enum import Enum


class Operation(Enum):
    """Operations"""

    DELETED = 1
    INSERTED = 2
    SUBSTITUTED = 3

    def __str__(self):
        return str(self.name.lower())


def min_calc(D, I, S):

    if D[0] <= I[0] and D[0] <= S[0]:
        return (D[0] + 1, Operation.DELETED)

    elif I[0] <= S[0]:
        return (I[0] + 1, Operation.INSERTED)

    else:
        return (S[0] + 1, Operation.SUBSTITUTED)


def distances(a, b):
    """Calculate edit distance from a to b"""

    # Append "0" to start of each string
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
        matrix[i][0] = (i, Operation.INSERTED)

    # Fill first column
    for j in range(1, length_b):
        matrix[0][j] = (j, Operation.DELETED)

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

    return matrix
