CC=cc
CCARGS=-ansi -O2

all: main

cipher.o:
	${CC} -ansi -O2 -c -o cipher.o cipher.c

main.o: cipher.o
	${CC} -ansi -O2 -c -o main.o main.c

main: main.o
	${CC} -ansi -O2 -o cipher main.o cipher.o

test.o: cipher.o
	${CC} -ansi -O2 -c -o test.o test.c

test: test.o
	${CC} -ansi -O2 -o test test.o cipher.o 
	./test

clean:
	rm -rf *.o test cipher
