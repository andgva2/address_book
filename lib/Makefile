CC := gcc
TARGET = liblinkedlist.so
TARGETFLAGS := -shared

SRC := ./liblinkedlist.c
HEADER := ./liblinkedlist.h

OBJDIR := ./../obj
OBJ := $(OBJDIR)/liblinkedlist.o
OBJFLAGS := -fPIC -c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(TARGETFLAGS) -o $@ $^

$(OBJ): $(SRC)
	mkdir -p $(OBJDIR)
	$(CC) $(OBJFLAGS) -o $@ $^

clean:
	$(RM) $(OBJ) $(TARGET)
