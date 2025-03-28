CC = gcc
CFLAGS = -Wall -g

build: main

main: main.o operations.o
	$(CC) -o main $^ 

main.o: main.c
	$(CC) $(CFLAGS) -c $^

operations.o: operations.c
	$(CC) $(CFLAGS) -c $^

run: build
	./main

clean:
	rm -f *.o main
	
pack:
	zip -FSr 314CA_SzaboCristina-Andreea_Tema1.zip README.md Makefile *.c *.h
