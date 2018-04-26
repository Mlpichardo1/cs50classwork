# Questions

## What's `stdint.h`? A "header shall declare sets of integer types
having specified widths, and shall define corresponding sets of macros.
It shall also define macros that specify limits of integer types
corresponding to types defined in other standard headers."

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?
A `uint8_t` is an 8-bit unsigned integer (range: 0 through 255 decimal).
A `uint32_t` is a 32-bit unsigned integer (range: 0 through 4294967295 decimal).
An `int32_t` is a 32-bit signed integer (range: –2147483648 through 2147483647 decimal).
A `uint16_t` is a 16-bit unsigned integer (range: 0 through 65535 decimal).


## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?
`BYTE`: is an 8-bit unsigned value that corresponds to a single octet in a network protocol.
`DWORD`: is a 32-bit unsigned integer (range: 0 through 4294967295 decimal).
`LONG`: A LONG is a 32-bit signed integer, in twos-complement format (range: –2147483648 through 2147483647 decimal).
`WORD`: A WORD is a 16-bit unsigned integer (range: 0 through 65535 decimal).

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be?
## Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."
Hex:    0x424d
ASCII:  BM (bitmap!)
This value is stored in "bfType".

## What's the difference between `bfSize` and `biSize`?
`bfSize`: The size, in bytes, of the bitmap file.
`biSize`: The number of bytes required by the structure.

## What does it mean if `biHeight` is negative?
If `biHeight` is negative, the bitmap is a top-down DIB and its origin is the upper-left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?
The number of bits-per-pixel. The `biBitCount` member of the BITMAPINFOHEADER structure determines
the number of bits that define each pixel and the maximum number of colors in the bitmap.

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?
If it cannot find the file, it will.

## Why is the third argument to `fread` always `1` in our code?
Because it specifies how many elements you want to read, and we're always
reading a struct so we only need 1 struct.

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?
The padding would be 3, because 3 pixels * 3 bytes per pixel * 3 padding = 12,
which is a multiple of 4.

## What does `fseek` do?
It moves to a specific location in a file.

## What is `SEEK_CUR`?
An integer constant which, when used as the 'whence' argument to the
fseek or fseeko function, specifies that the offset provided is relative to
the current file position.
