all:	
	gcc -c bisection.c
	gcc -o bisection bisection.o -lm

clean:
	rm *.o
