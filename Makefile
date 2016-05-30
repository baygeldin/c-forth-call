all:
	gcc -o main main.c foo.c -L/usr/local/lib -lffi
