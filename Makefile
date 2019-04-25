all: main

main: hash.o token.o tokenizer.o jc.c
	clang -g hash.o token.o tokenizer.o jc.c -o jc

tokenizer.o: tokenizer.c
	clang -g -c tokenizer.c
	
token.o: token.c
	clang -g -c token.c
	
hash.o: hash.c
	clang -g -c hash.c

clean:
	rm -rf *.o

clobber: clean
	rm -rf jc

