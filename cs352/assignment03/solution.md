Homework 3
==========

By Josh Davis

Due: Thurs, Feb 7 at midnight

## Problem 1 (40pts)
*Parent process in parentheses*

1. P0
2. P1 (P0)
3. P2 (P0)
4. P3 (P0)
5. P4 (P1)
6. P5 (P1)
7. P6 (P2)
8. P7 (P5)

### Tree

               (P0)
           /    |    \
         (P1)  (P3)  (P2)
        /    \        |
      (P4)   (P5)    (P6)
              |
             (P7)

## Problem 2 (30pts)

1. A: pid = 0
2. B: pid1 = 5000
3. C: value = 1
4. D: pid = 5000
5. E: pid1 = 3000
6. F: value = 2

## Problem 3 (30pts)

### Possibility 1

    This is the child process 2.
    This is the child process 1.
    This is parent process.

There doesn't seem to be any other possibilities of output because of the order
of read() and write().

At the first fork, we have two possibilities: parent runs or child runs.

#### Parent Runs First

If the parent runs, it goes onto the else statement and then forks again. Again
we have two possibilities, the parent or child.

 1. If the parent runs, it is immediately held up by the read() and waits for
    something to be written to fd0.

 2. If the child runs, it will enter the if statement and print "This is child
    process 2." and then write to fd0 and exit.

#### Child Runs First

If the child runs first, it goes into the if statement and then tries to read()
from fd0. At this point it then is blocked and MUST execute the parent.

The parent then executes and does a fork(). There are two possibilities again:

 1. If the parent runs, it does a read() from fd1. Fd1 has nothing written to it
    so it blocks. Now the only process that isn't blocked is the second child.

    The second child will then print out "This is child processs 2." and then
    must then execute the first child because fd1 hasn't been written to. Thus
    "This is child process 1." is then printed.

    Lastly, the read() on fd1 can now continue and prints "This is parent
    process.".

 2. If the child runs, it will print "This is child process 2." and then
    continue on with the first child ".. child process 1" and then finally the
    last print "This is parent process."

Therefore there only seems to be one way for the output to be printed.
