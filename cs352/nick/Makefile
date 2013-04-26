CC = gcc
FLAGS = -std=c99 -g

all: rw_test

rw_test: rw_test.o pipe_sem.o
	${CC} ${FLAGS} pipe_sem.o rw_test.o -o rw_test -lpthread

pipe_sem.o: pipe_sem.c pipe_sem.h
	${CC} ${FLAGS} -O -c pipe_sem.c
	
rw_test.o: rw_test.c pipe_sem.h
	${CC} ${FLAGS} -O -c rw_test.c
	


clean:
	rm *.o
	rm rw_test
