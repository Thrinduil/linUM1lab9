CC = gcc
INSTALLDIR = /usr/local/bin

all:		program

program:	main.c
		$(CC) -o electrotest-standalone main.c

install:	program
		cp electrotest-standalone $(INSTALLDIR)
