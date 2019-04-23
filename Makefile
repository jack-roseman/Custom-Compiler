all: main

main: hash.o main.c
	clang -g hash.o main.c -o main

hash.o: hash.c
	clang -g -c hash.c

clean:
	rm -rf *.o

clobber: clean
	rm -rf main

