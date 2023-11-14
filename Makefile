all: build install

build:
	$(CC) -o calc main.c

install:
	cp calc $(HOME)/System/bin
