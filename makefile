CC = gcc
INSTALLDIR = /usr/local/bin

all:		program

program:	electrotest-standalone.c
		$(CC) -o electrotest-standalone electrotest-standalone.c

install:	program
		cp electrotest-standalone $(INSTALLDIR)
