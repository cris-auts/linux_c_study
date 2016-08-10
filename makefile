target: main.o stack.o
	cc -o main main.o stack.o

main.o: main.c
	cc -c main.c

stack.o: stack.c
	cc -c stack.c


clean:
	rm *.o main
