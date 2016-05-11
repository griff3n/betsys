CC=gcc
CFLAGS=-std=c11 -pedantic -Wall -Werror
CDEBUGFLAGS=-g -O0
SOURCES=$(addprefix src/, MindenMiniShell.c)
BIN=bin


.PHONY: all compilemain debugmain runmain makedir clean

all: clean runmain

runmain: compilemain
	./$(BIN)/MindenMiniShell

compilemain: makedir
	$(CC) $(CFLAGS) $(SOURCES) -o $(BIN)/MindenMiniShell

debugmain: clean makedir
	$(CC) $(CFLAGS) $(CDEBUGFLAGS) $(SOURCES) -o $(BIN)/MindenMiniShell

makedir:
	mkdir -p $(BIN)

clean:
	rm -rf $(BIN)/