all: main.o parse.o
	gcc -o shell main.o parse.o
main.o: main.c parse.h
	gcc -c main.c
parse.o: parse.c parse.h
	gcc -c parse.c
run: 
	./shell
clean: 
	rm *.o

