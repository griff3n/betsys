CC=gcc
CFLAGS=-std=c11 -pedantic -Wall
CDEBUGFLAGS=-g -O0
SOURCES=$(addprefix src/, main.c)
BIN=bin


.PHONY: all compilemain debugmain runmain makedir clean

all: clean runmain

runmain: compilemain
	./$(BIN)/main ~/workspace/c/betsys/test 5

compilemain: makedir
	$(CC) $(CFLAGS) $(CDEBUGFLAGS) $(SOURCES) -o $(BIN)/main -lpthread

debugmain: clean makedir
	$(CC) $(CFLAGS) $(CDEBUGFLAGS) $(SOURCES) -o $(BIN)/main -lpthread

makedir:
	mkdir -p $(BIN)

clean:
	rm -rf $(BIN)/