#Current make system
BIN=./bin/
HEADER=./headers/
SOURCE=./src/
CC=gcc
OUT=./out/


all: build
	./$(BIN)main

build: $(HEADER)*.h $(SOURCE)*.c  
	$(CC) -Wall -g -o $(BIN)main  $(SOURCE)*.c -lm

valgrind: 
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./$(BIN)main