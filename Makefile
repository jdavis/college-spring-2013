CC=gcc

build: faked_uname.c
	$(CC) -w -o faked_uname faked_uname.c
