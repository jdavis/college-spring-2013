Homework 1
==========

By Josh Davis
Due: Thurs, Jan 24 at midnight

## Problem 1 (20pts)

a: Initalized data segment (global variable)
b: Stack (just a char pointer)
c: Stack (just a char)
b\*: Heap (because of malloc)

## Problem 2 (50pts)

### Mono-Programming

    j1  |--------------45             --------------45
    io1 |              --------------45
    j2  |                                           -----------------54                -----------------54
    io2 |                                                            -----------------54
        |______________________________________________________________________________________________
          10 20 30 40 50 60 70 80 90 100 110 120 130 140 150 160 170 180 190 200 210 220 230 240 250 260

T = job 1 comp. + job 1 io + job 1 io comp. + job 2 comp + job 2 io + job 2 io comp
T = 45 + 45 + 45 + 54 + 54 + 54
T = 297

### Multi-Programming

    j1  |-------------45            ------------45
    j2  |             --------------54         (9s) -------------54
    io1 |             -------------45
    io2 |                           -------------54
        |______________________________________________________
          10 20 30 40 50 60 70 80 90 100 110 120 130 140 150 160

T = job 1 comp. + job 2 comp. + job 1 io comp. + wait + job 2 io comp.
T = 45 + 54 + 45 + 9 + 54
T = 207 seconds


## Problem 3

### I/O Devices

All instructions that operate on any I/O devices could be part of the
privileged instruction set. In addition, the instructions could only be accessed
by using system calls.

### Memory

One way to protect memory is for the OS to keep track of the start and end of
the range of memory that it is allocated. This way, whenever the program uses an
instruction to alter the memory, it can check to determine if it is in the
available range. All other memory outside of the range is thus protected.

### CPU

The reason for protecting the CPU is to keep programs/users from hogging the
time of the CPU. One way to do this is to use a timer that interrupts the
computer after a specific time to check what is in control of the CPU. If the OS
isn't in control of the CPU it would mean the protection of the CPU has been
compromised.
