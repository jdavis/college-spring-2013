Homework 7
==========

By Josh Davis

Due: Thurs, March 14 at midnight

## Problem 1 (70pts)

Monitor in C to solve the producer-consumer problem.

    /* code here */

## Problem 2 (30pts)

The reader-writer problem implemented with "writer's priority" defined as
follows:

 1. At any time, shared file can be accessed by one writer exclusively, or one
    or multiple readers concurrently.

 2. Whenever there are both reader and writer processes arriving or waiting to
    access the shared file, the writer has higher priority than reader toa ccess
    the shared file.

### Pseudocode

    Monitor Reader-Writer
    begin
        readercount: integer 
        busy: boolean 
        OKtoread, OKtowrite: condition

        procedure startread
        begin
            If busy then OKtoread.wait;
            readercount := readercount + 1;
            OKtoread.signal
        end startread

        procedure endread;
        begin
            readercount := readercount-1;
            If readercount = 0 then OKtowrite.signal;
        end endread

        procedure startwrite;
        begin
            If busy or readercount <>0 then OKtowrite.wait;
            busy := true;
        end startwrite

        procedure endwrite;
        begin
            busy := false
            if OKtoread.queue then OKtoread.signal
            else OKtowrite.signal
        end endwrite

        begin /* initialization of local data */
            readercount := 0;
            busy := false;
        end
    end Reader-Writer
