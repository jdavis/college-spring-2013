SRC = src
TARGETS = makesquare partH partG cs2ppm ppm2cs imagestats darken lighten flip rotate matte convolve barcode
DEPS = cs229.o
#CFLAGS = -Wall -pedantic
CFLAGS = -Wall -pedantic
CC = gcc

all: $(DEPS) $(TARGETS)

$(TARGETS): $(DEPS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(DEPS): cs229.h

# Lighten symbolic link
lighten:
	ln -s ./darken ./lighten

# Part G
partG: MatrixMultiplier.class libmatrix.so
MatrixMultiplier.class: MatrixMultiplier.java
	javac MatrixMultiplier.java
	javah -jni MatrixMultiplier

libmatrix.so: matrix.c
	# Arch
	$(CC) $(CFLAGS) -fPIC -I/opt/java/include -I/opt/java/include/linux matrix.c -shared -o libmatrix.so

	# Pyrite
	#gcc -pedantic -Wall -I/usr/lib/jvm/java-openjdk/include -I/usr/lib/jvm/java-openjdk/include/linux -fPIC -pipe -c matrix.c -shared -o libmatrix.so

# Part H
partH: DisplayRunner.class

DisplayRunner.class: DisplayRunner.java CS229.java
	javac DisplayRunner.java

clean:
	rm *.o

cleandist:
	rm -f $(TARGETS)
	rm -f *.class
	rm -f *.o
	rm libmatrix.so
