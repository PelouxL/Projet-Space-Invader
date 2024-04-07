CC = gcc
CFLAGS = -W -Wall -std=c89 -pedantic -O2

EXEC_FILES = occu huffman

all : $(EXEC_FILES)

huffman: huffman.c
	$(CC) $(CFLAGS) $^ -o $@

occu : occurence.c
	$(CC) $(CFLAGS) $^ -o $@

clean :
	rm *.o $(EXEC_FILES)
