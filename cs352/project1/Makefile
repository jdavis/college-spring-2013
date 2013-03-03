CFLAGS = -ggdb -Wall -pedantic
CC = gcc

$(TARGETS): $(DEPS)

test: test.c lib-ult.c
	$(CC) $(CFLAGS) test.c -o test

switch: switch.c lib-ult.c
	$(CC) $(CFLAGS) switch.c -o switch

run-test: test
	./test > test.txt
	diff test.txt output.txt

run-switch: switch
	./switch

clean:
	rm test
	rm *.o
