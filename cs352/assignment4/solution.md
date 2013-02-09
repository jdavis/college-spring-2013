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
