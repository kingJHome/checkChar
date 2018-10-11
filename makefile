main: main.c
	gcc -o main main.c

mainDebug: main.c
	gcc -g main.c -o mainDebug
