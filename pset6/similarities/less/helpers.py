from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""

    # Initialize return list
    return_lines = []

    # Parse strings by line-break and convert to lists
    list_a = a.split('\n')
    list_b = b.split('\n')

    # Search for matching lines
    for a in list_a:
        for b in list_b:
            if a == b:
                return_lines.append(a)

    # Delete duplicates
    return_lines = list(set(return_lines))

    # Return identical lines in a and b
    return return_lines


def sentences(a, b):
    """Return sentences in both a and b"""

    # Initialize return list
    return_sentences = []

    # Parse strings into sentences and convert to list
    list_a = sent_tokenize(a)
    list_b = sent_tokenize(b)

    # Search for matching lines
    for a in list_a:
        for b in list_b:
            if a == b:
                return_sentences.append(a)

    # Delete duplicates
    return_sentences = list(set(return_sentences))

    # Return identical sentences in a and b
    return return_sentences


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    # Initialize return list
    return_substrings = []

    # Calculate string lengths
    len_a = len(a)
    len_b = len(b)

    # Parse strings into substrings and convert to list
    list_a = [a[i:i+n] for i in range(len_a - n + 1)]
    list_b = [b[j:j+n] for j in range(len_b - n + 1)]

    # Search for matching lines
    for a in list_a:
        for b in list_b:
            if a == b:
                return_substrings.append(a)

    # Delete duplicates
    return_substrings = list(set(return_substrings))

    # Return identical substrings in a and b
    return return_substrings
