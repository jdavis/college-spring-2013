CFLAGS = -Wall -pedantic
CC = gcc

$(TARGETS): $(DEPS)

test: test.c lib-ult.c
	$(CC) $(CFLAGS) test.c -o test

run: test
	./test > test.txt
	diff test.txt output.txt

clean:
	rm -f $(TARGETS)
	rm -f *.o
