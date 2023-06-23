CC = gcc

CFLAGS = -g -Wall

INCLUDES = -I./src

LFLAGS = -L./lib

LIBS = -llinkedlist

TARGET = address_book

SRCS = $(TARGET).c liblinkedlist.c

OBJS = $(SRCS:.c=.o)



all: $(TARGET)
	
$(TARGET): $(OBJS)
	mkdir -p ./bin/
	$(CC) $(CFLAGS) $(INCLUDES) -o ./bin/$(TARGET) ./src/$(TARGET).c && echo A

$(TARGET).o: ./src/$(TARGET).c ./src/liblinkedlist.c ./src/liblinkedlist.h
	mkdir -p ./obj/
	$(CC) $(CFLAGS) -c ./src/$(TARGET).c -o ./obj/$(TARGET).o && echo a
	
liblinkedlist.o: ./src/liblinkedlist.c ./src/liblinkedlist.h
	mkdir -p ./obj/
	$(CC) $(CFLAGS) -c ./src/liblinkedlist.c -o ./obj/liblinkedlist.o && echo b

clean:
	$(RM) -r ./bin/ ./obj

#TODO: target called by your program name
#TODO: target for building .o files
#Implicit variables is a must
