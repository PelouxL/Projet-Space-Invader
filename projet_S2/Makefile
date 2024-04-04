CC = gcc
CFLAGS = -W -Wall -std=c89 -pedantic -O2

EXEC_FILES = occu 

all : $(EXEC_FILES)

occu : occurence.c
	$(CC) $(CFLAGS) $^ -o $@

clean :
	rm *.o $(EXEC_FILES)