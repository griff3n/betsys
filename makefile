CC=gcc
CFLAGS=-std=c11 -pedantic -Wall
CDEBUGFLAGS=-g -O0
SOURCES=$(addprefix src/, myScheduler.c)
BIN=bin


.PHONY: all compilemain debugmain runmain makedir clean

all: clean debugmain

runmain: compilemain
	./$(BIN)/myScheduler

compilemain: makedir
	$(CC) $(CFLAGS) $(SOURCES) -o $(BIN)/myScheduler

debugmain: clean makedir
	$(CC) $(CFLAGS) $(CDEBUGFLAGS) $(SOURCES) -o $(BIN)/myScheduler

makedir:
	mkdir -p $(BIN)

clean:
	rm -rf $(BIN)/