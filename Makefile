all: main foo
	gcc main.o foo.o -o main

main: main.c
	gcc -c $@.c -o $@.o

foo: foo.c
	gcc -c $@.c -o $@.o
