# Pentomino-puzzle-solver-in-C
A pentomino solver written in C, I tried to make it fast and featureful.

The usage message, printed when you run the program with no command line arguments, explains how to use it. Here is the usage message:

```
=== Pentomino puzzle solution finder ===
Usage and command line options:
 -w [width] 
 -h [height] 
 -board [board string. Refer to the example commands] 
 -n [number of solutions to stop at, default 1] 
 -all (don't stop until search is exhausted)
 -pieces [binary string / list of booleans enabling/disabling the use of specific pieces. Refer to the piece index reference]
 -style [number] (choose the style you want to display the solutions in)
   (0: rounded edges (bigger)  1: sharpened lines (smaller)  2: simple/plain) 

=== Example commands ===
Try copy pasting these example commands:

Example 1:
./a.out  -w 20  -h 3

Example 2:
./a.out  -w 12  -h 5  -n 2

Example 3:
./a.out  -w 5 -h 5  -style 1

Example 4:
./a.out -board '
#..............#
................
................
#..............#'

Example 5:
./a.out -board '
............
............
#........#..
##......###.
##.......#..' -all -pieces 011111111011

=== Piece index reference ===
This informs you which index of the binary string corresponds to which pentomino piece.
The hex number used to draw a piece is its index value.

 37777255511abbbbb088
 37442225116aaa990008
 3334442516666a999088
```
