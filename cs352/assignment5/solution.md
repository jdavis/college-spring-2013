Homework 5
==========

By Josh Davis

Due: Thurs, Feb 21 at midnight

## Problem 1 (70pts)

### Part a

Show Gantt charts for the following:

#### First Come First Serve

    |
    |------------P1-------------|P2-|-P3-|P4-|----P5------|
    |________________________________________________________
                  5             10            15            20                    

#### Non-preemptive SJF

    |
    |------------P1-------------|P2-|-P4|P3--|----P5------|
    |________________________________________________________
                  5             10            15            20                    

    PX-- means two units, PX- means one unit

#### Preemptive Priority

    |
    |P1-|P2-|P1-|-------P5----|----------P1----------|P3--|
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

#### Non-preemptive SJF

#### Preemptive Priority

#### Round Robin

### Part c

What is the average waiting time of all process for each scheduling algorithm?

## Problem 2 (30pts)

### Part a

Time quantum is 1 millisecond.

### Part b

Time quantum is 10 milliseconds.
