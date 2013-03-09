TARGETS = test switch
CFLAGS = -ggdb -Wall -pedantic
DEPS = priority.o
CC = gcc

$(TARGETS): $(DEPS)

run-test: test
	./test > test.txt
	diff test.txt output.txt

run-switch: switch
	./switch

clean:
	rm test
	rm *.o
