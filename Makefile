CC = gcc

objects = address_book

all: $(objects)
	
address_book: address_book.c liblinkedlist.c liblinkedlist.h
	$(CC) $< -o $@

clean:
	rm -f address_book

#TODO: target called by your program name
#TODO: target for building .o files
#Implicit variables is a must
