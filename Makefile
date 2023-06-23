CC = gcc

CFLAGS = -g -Wall

INCLUDES = -I./src/

LFLAGS = -L./lib/

LIBS = -llinkedlist

TARGET = address_book

SRCS = $(TARGET).c liblinkedlist.c

OBJS = $(SRCS:.c=.o)



all: $(TARGET)
	
$(TARGET): $(OBJS)
	mkdir -p ./bin/
	$(CC) $(CFLAGS) $(INCLUDES) -o ./bin/$(TARGET) ./src/$(TARGET).c

$(TARGET).o: ./src/$(TARGET).c ./src/liblinkedlist.c ./src/liblinkedlist.h
	mkdir -p ./obj/
	$(CC) $(CFLAGS) -c ./src/$(TARGET).c -o ./obj/$(TARGET).o
	
liblinkedlist.o: ./src/liblinkedlist.c ./src/liblinkedlist.h
	mkdir -p ./obj/
	$(CC) $(CFLAGS) -c ./src/liblinkedlist.c -o ./obj/liblinkedlist.o

clean:
	$(RM) -r ./bin/ ./obj
