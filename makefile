CC=gcc
CFLAGS=-std=c11 -pedantic -Wall
CDEBUGFLAGS=-g -O0
SOURCES=$(addprefix src/, Main.c)
BIN=bin


.PHONY: all compilemain debugmain runmain makedir clean

all: clean debugmain

runmain: compilemain
	./$(BIN)/MindenMiniShell

compilemain: makedir
	$(CC) $(CFLAGS) $(SOURCES) -o $(BIN)/Main

debugmain: clean makedir
	$(CC) $(CFLAGS) $(CDEBUGFLAGS) $(SOURCES) -o $(BIN)/Main

makedir:
	mkdir -p $(BIN)

clean:
	rm -rf $(BIN)/