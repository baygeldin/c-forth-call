all:
	gcc -o main main.c foo.c -rdynamic -L/usr/lib:/usr/local/lib -lffi -ldl
