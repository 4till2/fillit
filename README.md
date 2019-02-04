# 42_Fillit
A re-implementation of the unix "ls" command implemented in C.

## Description
The program takes a file as parameter, which contains a list of Tetriminos, and arranges them
in the smallest square possible. The main goal is to find the smallest square in the minimal amount amount of time.

The executable takes as a parameter, a file which contains a list of Tetriminos
to assemble. This file has a very specific format : every Tetrimino must exactly fit in a
4 by 4 chars square and all Tetrimino are separated by an newline each.
If the number of parameters sent to the executable is not 1, the program displays
its usage and exits properly. If a Tetrimino is invalid the program displays error and exits properly. 

The description of a Tetriminos must respect the following rules :
• Precisely 4 lines of 4 characters, each followed by a new line (well... a 4x4 square).
• A Tetrimino is a classic piece of Tetris composed of 4 blocks.
• Each character must be either a block character(’#’ ) or an empty character (’.’).
• Each block of a Tetrimino must touch at least one other block on any of his 4 sides
(up, down, left and right).

A few examples of valid descriptions of Tetriminos:
```
.... .... #### .... .##. .... .#.. .... ....
..## .... .... .... ..## .##. ###. ##.. .##.
..#. ..## .... ##.. .... ##.. .... #... ..#.
..#. ..## .... ##.. .... .... .... #... ..#.
```
A few examples of invalid descriptions of Tetriminos
```
#### ...# ##... #.   .... ..## #### ,,,, .HH.
...# ..#. ##... ##   .... .... #### #### HH..
.... .#.. ....  #.   .... .... #### ,,,, ....
.... #... ....  .... ##.. #### ,,,, ....
```
Because each Tetrimino fills only 4 of the 16 available boxes, it is possible to describe
the same Tetrimino in multiple ways. However, a rotated Tetrimino describes a different
Tetrimino from the original, in the case of this project. This means no rotation is possible
on a Tetrimino, when you will arrange it with the others.
Those Tetriminos are then perfectly equivalents on every aspect :
```
##.. .##. ..## .... .... ....
#... .#.. ..#. ##.. .##. ..##
#... .#.. ..#. #... .#.. ..#.
.... .... .... #... .#.. ..#.
```
These 5 Tetriminos are, for their part, 5 distincts Tetriminos on every aspect :
```
##.. .### .... .... ....
#... ...# ...# .... .##.
#... .... ...# #... .##.
.... .... ..## ###. ....
```
Sample Usage:
```
$> cat sample.fillit | cat -e
....$
##..$
.#..$
.#..$
$
....$
####$
....$
....$
$
#...$
###.$
....$
....$
$
....$
##..$
.##.$
....$
$> ./fillit sample.fillit | cat -e
DDAA$
CDDA$
CCCA$
BBBB$
$>
```
For a more thorough description and list of requirements (such as allowed functions) look at "fillit.en.pdf".

### Functionality
The program has the following usage:
`fillit [valid file]`

### Usage
```
$ make
```

```
$ ./fillit [file]
```
