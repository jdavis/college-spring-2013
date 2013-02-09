Homework 4
==========

By Josh Davis

Due: Thurs, Feb 14 at midnight

## Problem 1 (30pts)

There are various situations in which a multithreaded solution might provide
better performance than a single threaded solution on a single processor system.

The reason for this is because often the case with programs is that they need to
do a action that requires a response from an outside object. These objects could
be a person inputting data, a read from the network, a read from a hard drive.
All of those things require time to wait before action can continue. However, if
the program is split up into multiple threads, execution can continue while
waiting for these events to happen.

A canonical examples is just about any application with an interface. There is
almost always a thread handling user input and another thread actually
performing the task. If this was not the case there would be a significant wait
between things. Like as I write this answer in Vim it is doing various
computations in the background (syntax highlighting for Markdown, dynamic
algorithms for word wrapping, etc.) and yet it responds to every keystroke
seemingly instantly. This would be very hard to do with just one thread.

## Problem 2 (30pts)

    main():
        i = 3
        call pthread_create with th_code
    th_code():
        nThreads = 1
        i = 2
        i > 0:
            th_code():
                nThreads = 2
                i = 1
                i > 0:
                    th_code():
                        nThreads = 3
                        i = 0
                        i > 0 == false

Using the diagram thingy from above there are three user level threads created.

## Problem 3 (40pts)

### Unforked main() threads
 1. Fork()
 2. do\_1 (with VM) (because var == 1)
 3. do\_2

### Forked main() threads
 4. do\_1 {forked} (with nothing)
 5. do\_2 {forked}

Following the execution we can get this:

    main()
        pid > 0: var = 1
        one printf: var = 1
    do_1() (with VM):
        var = 1
        var = 1 * 2 = 2
    do_2() (no VM):
        var = 1
        var (for thread) = 1 * 3 = 3
        one printf: Thread 2: var=3
    main() forked:
        var = 5
        one printf: var = 5
    do_1() {forked} (no VM:
        var = 5 (from fork)
        var (for thread) = 5 * 2 = 10
    do_2() {forked}:
        var = 5 (from fork)
        var (for thread) = 5 * 3 = 15
        one printf: Thread 2: var=15


Which will make the input:

    var = 1
    var = 5
    Thread 2: var=3
    Thread 2: var=15

There's money in the banana stand.
