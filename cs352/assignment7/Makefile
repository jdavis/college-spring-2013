TARGETS = test
CFLAGS = -ggdb -Wall -pedantic
DEPS = monitor.o
CC = gcc

$(TARGETS): $(DEPS)

zip:
	(cd ..; zip solution.zip assignment7/test.c assignment7/monitor.h assignment7/monitor.c assignment7/Makefile assignment7/solution.md; mv solution.zip assignment7/)

clean:
	rm test
	rm *.o
