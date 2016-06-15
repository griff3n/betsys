CC=gcc
CFLAGS=-std=c11 -pedantic -Wall
CDEBUGFLAGS=-g -O0
SOURCES=$(addprefix src/, mycp.c)
BIN=bin


.PHONY: all compilemain debugmain runmain makedir clean

all: clean runmain

runmain: compilemain
	./$(BIN)/mycp -o /home/peter/workspace/c/betsys/test/10.txt /home/peter/workspace/c/betsys/test/test.txt

compilemain: makedir
	$(CC) $(CFLAGS) $(SOURCES) -o $(BIN)/mycp

debugmain: clean makedir
	$(CC) $(CFLAGS) $(CDEBUGFLAGS) $(SOURCES) -o $(BIN)/mycp

makedir:
	mkdir -p $(BIN)

clean:
	rm -rf $(BIN)/