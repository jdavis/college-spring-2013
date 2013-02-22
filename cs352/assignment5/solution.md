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

#### First Come First Serve

    P1 = 0
    P2 = 10
    P3 = 11
    P4 = 13
    P5 = 14

    AWT = (0 + 10 + 11 + 13 + 14) / 5
        = 9.6

#### Non-preemptive SJF

    P1 = 0
    P2 = 10 - 1
       = 9
    P3 = 12 - 2
       = 10
    P4 = 11 - 3
       = 8
    P5 = 14 - 4
       = 10

    AWT = (0 + 10 + 12 + 11 + 14) / 5
        = 9.4

#### Preemptive Priority

    P1 = 3 + 5
       = 8
    P2 = 0
    P3 = 15 - 2
       = 13
    P4 = 18 - 3
       = 15
    P5 = 0

    AWT = (8 + 0 + 13 + 15 + 0) / 5
        = 7.2

#### Round Robin

    P1 = 9
    P2 = 1
    P3 = 1
    P4 = 2
    P5 = (15 - 5 - 4)
       = 6

    AWT = (9 + 1 + 1 + 2 + 6) / 5
        = 3.8

## Problem 2 (30pts)

### Part a

Time quantum is 1 millisecond.

For every context switch, it takes .1 ms to switch, therefore:

    CPU Utilization = (1 / 1.1) * 100
                    = 91%

### Part b

Time quantum is 10 milliseconds.

A context switch takes place every 1 ms and it goes through all 10 processes,
therefore:
    
    CPU Utilizaiton = 20/((10*1.1) * 100) * 100
                    = 94%
