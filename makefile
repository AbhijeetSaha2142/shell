all: main.o parse.o run.o
	gcc -o shell main.o parse.o run.o
main.o: main.c parse.h run.h
	gcc -c main.c
parse.o: parse.c parse.h
	gcc -c parse.c
run.o: run.c run.h parse.h
	gcc -c run.c
run: 
	./shell
clean: 
	rm *.o

