TARGETS = rw_test
CFLAGS = -ggdb -Wall -pedantic
CPPFLAGS = -pthread
DEPS = pipe_sem.o
CC = gcc

$(TARGETS): $(DEPS)

run: rw_test $(DEPS)
	./rw_test 5 0 0 1 1 0 1

clean:
	rm rw_test
	rm *.o
