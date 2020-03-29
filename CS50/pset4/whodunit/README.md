# Questions

## What's `stdint.h`?

Standard package library (functions) for standard inputs and outputs

TODO

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

Unsigned integers can be only positive and the first bit is not the signing bit. Assigned integers can be negative or positive, and the first bit is used as a signing bit.

TODO

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE = 1, DWORD = 4, LONG = 4, WORD = 2 bytes

TODO

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

BM


TODO

## What's the difference between `bfSize` and `biSize`?

bfSize is the size of the file, while the biSize is the requirement of bytes for the structure of the file

TODO

## What does it mean if `biHeight` is negative?

It is a topdown DIB, which cannot be compressed

TODO

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

TODO

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

If the file does not exist.

TODO

## Why is the third argument to `fread` always `1` in our code?

Because you only want to read it once.

TODO

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

TODO

## What does `fseek` do?

fseek allows you to change the file pointer to a different place. I am assuming this is to offset the header

TODO

## What is `SEEK_CUR`?


It is the input to fseek that allows you to set the pointer from the current location.

TODO
