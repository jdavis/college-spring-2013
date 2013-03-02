TARGETS = test
CFLAGS = -Wall -pedantic
CC = gcc

$(TARGETS): $(DEPS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

run: test
	./test > test.txt
	diff test.txt output.txt

clean:
	rm -f $(TARGETS)
	rm -f *.o
