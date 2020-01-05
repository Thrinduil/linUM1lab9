CC = gcc

all:		program

program:	main.c
		$(CC) -o electrotest main.c
