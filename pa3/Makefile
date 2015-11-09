CC = gcc
CFLAGS = -Wall -g -O2



all: index 


index: indexer.o tokenizer.o utils.o 
	$(CC) -g -Wall indexer.o tokenizer.o utils.o -o index 

indexer.o: indexer.c indexer.h 
	$(CC) $(CFLAGS) -c indexer.c 

tokenizer.o: tokenizer.c tokenizer.h
	$(CC) $(CFLAGS) -c tokenizer.c
utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c
clean: 
	rm index indexer.o tokenizer.o utils.o 

