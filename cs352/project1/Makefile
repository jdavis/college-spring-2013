TARGETS = test switch unit
CFLAGS = -ggdb -Wall -pedantic
DEPS = priority.o
CC = gcc

$(TARGETS): $(DEPS)

run-test: test lib-ult.c
	./test > test.txt
	diff test.txt output.txt

run-unit: unit lib-ult.c
	./unit

run-switch: switch
	./switch

clean:
	rm test
	rm *.o
