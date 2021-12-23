all: bvernan

bvernan: main.c  bvernan.c
	gcc -Wall main.c bvernan.c -O2 -o bvernan
debug:
	gcc -O0 -g -Wall main.c bvernan.c -o bvernan
clean:
	rm bvernan 
