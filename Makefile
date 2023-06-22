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
	$(CC) $(CFLAGS) $(INCLUDES) -o ./bin/$(TARGET) ./src/$(TARGET).c

$(TARGET).o: $(TARGET).c liblinkedlist.c liblinkedlist.h
	$(CC) $(CFLAGS) -c ./src/$(TARGET).c -o ./obj/$(TARGET).o

./obj/%.o : ./src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) ./bin/$(TARGET)

#TODO: target called by your program name
#TODO: target for building .o files
#Implicit variables is a must
