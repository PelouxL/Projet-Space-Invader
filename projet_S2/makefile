CC = gcc
CFLAGS = -W -Wall -std=c89 -pedantic -O2

EXEC_FILES = main

all : $(EXEC_FILES)

main: main.c huffman.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

huffman.o: huffman.c huffman.h
	$(CC) -c $(CFLAGS) $^

mgit:
	git add --all; git commit -m "cc c moi"; git push;

clean :
	rm *.o $(EXEC_FILES)
