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