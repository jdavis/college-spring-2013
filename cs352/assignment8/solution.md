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

#### Possible Executions

I'm just going to use this this document as scratch paper to try different
possibilities to try and find a deadlock

##### One
    P1 waits on s1, gets lock on s1
    P1 waits on s2, gets lock on s2
    P2 waits on s2, can't proceed

    No deadlock...

##### Two
    P2 waits on s2, gets lock on s2
    P2 waits on s3, gets lock on s3
    P1 waits on s1, gets lock on s1
    P1 waits on s2, can't proceed
    P2 signals s2
    P2 waits on s1, can't proceed
    P1 continues, gets lock on s2
    P1 waits on s3, can't proceed

    P2 is waiting on s1 and can't proceed
    P1 is waiting on s3 and can't proceed

    DEADLOCK!

So yes, it is possible that P1 and P2 can run into a deadlock. Here is how we
can prevent it by altering P2:

##### P2 New Code TODO
    wait(s2);
    y = y*2;
    wait(s3);
    z = z - y;
    signal(s2);
    wait(s1);
    x = x + z;
    signal(s1);
    signal(s3)

### Part B

#### Possible Executions

I'm just going to use this this document as scratch paper to try different
possibilities to try and find a deadlock

##### One
    P1 waits on s1, gets lock on s1
    P1 waits on s2, gets lock on s2
    P3 waits on s3, gets lock on s3
    P1 waits on s3, can't proceed
    P3 signals s2 and s3
    P3 waits on s1, can't proceed
    P1 gets lock on s3
    P1 signals, s3, s2, s1
    P3 gets lock on s1
    P3 signals s1, finishes execution

    No deadlock

##### Two
    P3 waits on s2, gets lock on s2
    P1 waits on s1, gets lock on s1
    P1 waits on s2, can't proceed
    P3 waits on s3, gets lock on s3
    P3 signals s3, s2
    P3 waits on s1, can't proceed
    P1 proceeds
    P1 signals s3, s2, s1
    P3 finishes execution

    No deadlock

Those aren't the only two possibilities but there doesn't seem to a way to end
up in a deadlock. Therefore there doesn't need to be any change to P3.

## Problem 2 (50pts)

### Part A

Need Matrix
Need[i,j] = Max[i,j] - Alloc[i,j]

       A B C D
    P0 0 0 0 0
    P1 0 7 5 0
    P2 0 0 2 0
    P3 1 0 1 2
    P4 0 6 4 2

### Part B

The system is in a safe state if all processes can finish executing. So as long
as there is one set of requests that would allow each to acquire its maximum
resources and then terminate.

A set of such requests is below:
1. P0 requests <0, 0, 0, 0>:
    Available: <1, 5, 2, 0> - <0, 0, 0, 0> = <1, 5, 2, 0>
2. P0 terminates and releases resources
    Available: <1, 5, 2, 0> + <0, 0, 1, 2> = <1, 5, 3, 2>
3. P2 requests <0, 0, 2, 0> and finishes:
    Available: <1, 5, 3, 2> + <0, 6, 3, 2> = <1, 11, 6, 5>
4. P1 requests <0, 7, 5, 0> and finishes:
    Available: <1, 11, 6, 5> + <1, 0, 0, 0> = <2, 11, 6, 5>
5. P3 requests: <1, 0, 1, 2> and finishes:
    Available: <2, 11, 6, 5> + <1, 3, 4, 4> = <3, 14, 10, 9>
6. P4 requests: <0, 6, 4, 2> and finishes:
    Available: <3, 14, 10, 9> + <0, 0, 1, 4> = <3, 14, 11, 13>

Since we have found one possible set of requests that allow the system to finish
execution, it **is** in a safe state.

### Part 3

Yes, the request can be granted immediately. Since there are <1, 5, 2, 0>
resources available, each value is greater than the value requested.

Therefore when the request is granted, the available resources becomes the
following:
    Available: <1, 5, 2, 0> - <0, 4, 2, 0> = <1, 1, 0, 0>
