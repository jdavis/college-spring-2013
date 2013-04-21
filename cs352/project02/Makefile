TARGETS = rw_test
CFLAGS = -ggdb -Wall -pedantic
CPPFLAGS = -pthread
DEPS = pipe_sem.o
CC = gcc
CPP = g++

rw_test: $(DEPS)
	$(CPP) -o rw_test rw_test.cpp $^ $(CPPFLAGS)

clean:
	rm rw_test
	rm *.o
