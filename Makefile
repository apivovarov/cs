cdir = src/main/c

.PHONY: all
all: fib


fib : ${cdir}/fib.c
	mkdir -p bin
	cc -o bin/fib ${cdir}/fib.c

.PHONY : clean
clean : 
	rm bin/fib
