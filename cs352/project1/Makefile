TARGETS = test
CFLAGS = -Wall -pedantic
CC = gcc

all: $(DEPS) $(TARGETS)

$(TARGETS): $(DEPS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f $(TARGETS)
	rm -f *.o
