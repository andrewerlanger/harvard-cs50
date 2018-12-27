# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

Probably not something you want to have.

## According to its man page, what does `getrusage` do?

It returns *resource usage measures* for 'who', which in our case (RUSAGE_SELF) means
resource usage statistics for the calling process (the sum of resources used by all threads).

## Per that same man page, how many members are in a variable of type `struct rusage`?

16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

Because passing large structs by value (rather than reference) takes up a lot of *memory* and could lead to stack overflow.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

The loop runs until the end of the file, reading one character at a time. Here's how it works:

    1. It first takes a character and checks whether it's an alphabetical character or apostrophe (when index > 0).
    If so, we're dealing with a work and so it appends the character to our char* word and then increases the index by 1.
    But it also then checks whether the index is longer than the longest word in the English language.
    If this is indeed the case, it consumes the read of the string with a while loop, as it can't be a word.

    2. If the character the loop takes is a digit, we can ignore that alphanumeric string it for the spell check.
    Using an else if statement, the program checks for digits and, if it finds one, consumes the rest of that particular string.

    3. Finally, if the index is greater than 0 and the character returned isn't a letter or number (or apostrophe):
    We must be at the end of a word.
    In this case, we terminate the char* word, update our word counter, and then check the words spelling.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

Here's what fscanf would do:
Read subsequent characters until whitespace is found. Here, whitespace can mean:
    1. blank
    2. new line
    3. tab
The problem is that some words end with punctuation (rather than whitespace).
This punctuation would be treated as another character, and thus we wouldn't know we were at the end of the word.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

To make sure the string is not inadvertedly edited within the function?
