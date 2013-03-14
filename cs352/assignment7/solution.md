Homework 7
==========

By Josh Davis

Due: Thurs, March 14 at midnight

## Problem 1 (70pts)

For the code to the monitor in C to solve the producer-consumer problem, look at
the source files included with the zip.


## Problem 2 (30pts)

The reader-writer problem implemented with "writer's priority" defined as
follows:

 1. At any time, shared file can be accessed by one writer exclusively, or one
    or multiple readers concurrently.

 2. Whenever there are both reader and writer processes arriving or waiting to
    access the shared file, the writer has higher priority than reader to access
    the shared file.

The logic of the pseudocode is that a reader only starts when there are no
writers accessing or when there are no writers in the queue. This gives priority
to the writers thus solving the solution.

### Modified Pseudocode

    Monitor Reader-Writer
    begin
        readercount: integer 
        busy: boolean 
        OKtoread, OKtowrite: condition

        procedure startread
        begin
            If busy or Oktowrite.queue then Oktoread.wait
            readercount := readercount + 1
            Oktoread.signal
        end startread

        procedure endread;
        begin
            readercount := readercount - 1
            If readercount = 0 then Oktowrite.signal
        end endread

        procedure startwrite;
        begin
            If busy or readercount <> 0 then Oktowrite.wait;
            busy := true;
        end startwrite

        procedure endwrite;
        begin
            busy := false;
            If Oktowrite.queue Oktowrite.signal
            else Oktoread.signal
        end endwrite

        begin /* initialization of local data */
            readercount := 0;
            busy := false;
        end
    end Reader-Writer
