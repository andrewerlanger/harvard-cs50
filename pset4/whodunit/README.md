# Questions

## What's `stdint.h`?

It's a header file in the C standard library.
Using macros, it provides a set of typedefs that specify exact-width integer types.
It also defines *minimum* and *maximum* allowable values for each type.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

You can fill up exactly the amount of space you want in a file.
This is good for things like bitmap headers.
Also: unsigned integers can only represent *positive* values

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE: 1
DWORD: 4
LONG: 4
WORD: 2

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

ASCII: BM

## What's the difference between `bfSize` and `biSize`?

bfSize: size of bitmap *file* (in bytes)
biSize: number of bytes required by the *structure*

## What does it mean if `biHeight` is negative?

The bitmap is *top-down* – its origin is the upper-left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

Maybe if the files don't exist? Bingo, or if it can't find the file.

## Why is the third argument to `fread` always `1` in our code?

Because we're reading one unit (whatever that unit may be) at a time?

Or, in other words:
Because it specifies how many elements you want to read.
We're always reading a struct (inc the colours) so we only need 1 struct.

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

In this case: skip over padding (if there is any).
In general: Itmoves to a specific location in a file.

## What is `SEEK_CUR`?

An integer constant.
When used as the 'whence' argument to the fseek or fseeko function, it specifies that the
offset provided is relative to the current file position.