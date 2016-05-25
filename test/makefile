CC=gcc
CFLAGS=-std=c11 -pedantic -Wall
CDEBUGFLAGS=-g -O0
SOURCES=$(addprefix src/, main.c)
BIN=bin


.PHONY: all compilemain debugmain runmain makedir clean

all: clean runmain

runmain: compilemain
	./$(BIN)/main ~/workspace/c/betsys

compilemain: makedir
	$(CC) $(CFLAGS) $(SOURCES) -o $(BIN)/main

debugmain: clean makedir
	$(CC) $(CFLAGS) $(CDEBUGFLAGS) $(SOURCES) -o $(BIN)/main

makedir:
	mkdir -p $(BIN)

clean:
	rm -rf $(BIN)/