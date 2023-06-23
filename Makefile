CC = gcc
CFLAGS = -g -Wall
TARGET = address_book

INCLUDES = -I./src/

LFLAGS = -L./lib/
LIBS = -llinkedlist

SRCS = $(TARGET).c liblinkedlist.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)
	
$(TARGET): ./obj/$(OBJS)
	mkdir -p ./bin/
	$(CC) $(CFLAGS) $(INCLUDES) -o ./bin/$(TARGET) ./src/$(TARGET).c

./obj/%.o: ./src/%.c
	mkdir -p ./obj/
	$(CC) $(CFLAGS) -c $< -o $@
	
liblinkedlist.o: ./src/liblinkedlist.c ./src/liblinkedlist.h
	mkdir -p ./obj/
	$(CC) $(CFLAGS) -c ./src/liblinkedlist.c -o ./obj/liblinkedlist.o

clean:
	$(RM) -r ./bin/ ./obj
