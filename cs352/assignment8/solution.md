Homework 8
==========

By Josh Davis

Due: Thurs, March 28 at midnight

## Problem 1 (50pts)

Semaphores:
* `s1` corresponds to `x`
* `s2` corresponds to `y`
* `s3` corresponds to `z`

### Part A

**Deadlock for P1 and P2?:** Yes

#### Execution

    1.1 P1 waits on s1, gets lock on s1
    1.2 Executes fine
    2.1 P2 waits on s2, gets lock on s2
    1.3 P1 waits on s2, can't enter

### Part B

**Deadlock:**

## Problem 2 (50pts)

