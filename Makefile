list: list.c list.h
	gcc -std=c99 -o list list.c

clean:
	rm -f list *.o
