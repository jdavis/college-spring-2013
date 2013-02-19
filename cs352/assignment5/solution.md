Homework 5
==========

By Josh Davis

Due: Thurs, Feb 21 at midnight

## Problem 1 (70pts)

### Part a

Show Gantt charts for the following:

#### First Come First Serve

    |
    |------------P1-------------|P2-|P3--|P4-|----P5------|
    |________________________________________________________
                  5             10            15            20                    

    PX-- means two units, PX- means one unit

#### Non-preemptive SJF

    |
    |------------P1-------------|P2-|-P4|P3--|----P5------|
    |________________________________________________________
                  5             10            15            20                    

    PX-- means two units, PX- means one unit

#### Preemptive Priority

    |
    |P1-|P2-|P1-|-----P5---|----------P1--------|P3--|P4-|
    |________________________________________________________
                  5             10            15            20                    

    PX-- means two units, PX- means one unit

#### Round Robin


    |
    |P1--|P2-|P3--|P4-|P5--|P1--|P5--|P1--|P5-|------P1---|
    |________________________________________________________
                  5             10            15            20                    

    PX-- means two units, PX- means one unit

### Part b

What is the turnaround time of each process for each scheduling algorithm?

#### First Come First Serve

    P1 = 10 + (0 - 0)
       = 10
    P2 = 1 + (11 - 1)
       = 11
    P3 = 2 + (12 - 2)
       = 12
    P4 = 1 + (14 - 3)
       = 12
    P5 = 5 + (15 - 4)
       = 16

#### Non-preemptive SJF

    P1 = 10 + (0 - 0)
       = 10
    P2 = 1 + (11 - 1)
       = 11
    P3 = 2 + (13 - 2)
       = 13
    P4 = 1 + (14 - 3)
       = 12
    P5 = 5 + (15 - 4)
       = 16

#### Preemptive Priority

    P1 = 10 + (16 - 0)
       = 26
    P2 = 1 + (2 - 1)
       = 2
    P3 = 2 + (18 - 2)
       = 18
    P4 = 1 + (18 - 3)
       = 16
    P5 = 5 + (8 - 4)
       = 9

#### Round Robin

    P1 = 10 + (19 - 0)
       = 29
    P2 = 1 + (3 - 1)
       = 3
    P3 = 2 + (5 - 2)
       = 5
    P4 = 1 + (6 - 3)
       = 4
    P5 = 5 + (15 - 4)
       = 16

### Part c

What is the average waiting time of all process for each scheduling algorithm?

## Problem 2 (30pts)

### Part a

Time quantum is 1 millisecond.

### Part b

Time quantum is 10 milliseconds.
