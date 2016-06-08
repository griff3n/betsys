CC=gcc
CFLAGS=-std=c11 -pedantic -Wall
CDEBUGFLAGS=-g -O0
SOURCES=$(addprefix src/, myls.c)
BIN=bin


.PHONY: all compilemain debugmain runmain makedir clean

all: clean runmain

runmain: compilemain
	./$(BIN)/myls

compilemain: makedir
	$(CC) $(CFLAGS) $(SOURCES) -o $(BIN)/myls

debugmain: clean makedir
	$(CC) $(CFLAGS) $(CDEBUGFLAGS) $(SOURCES) -o $(BIN)/myls

makedir:
	mkdir -p $(BIN)

clean:
	rm -rf $(BIN)/