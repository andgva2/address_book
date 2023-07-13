CC := gcc
BINDIR := ./../bin
TARGET = address_book

SRC := ./$(TARGET).c

OBJDIR := ./../obj
OBJ := $(OBJDIR)/$(TARGET).o

LFLAGS := -L./../lib
LIBS := -llinkedlist

INCLUDEFLAGS := -I./../lib

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	mkdir -p $(BINDIR)
	$(CC) -o $(BINDIR)/$@ $^ $(LIBS) $(LFLAGS)

$(OBJ): $(SRC)
	mkdir -p $(OBJDIR)
	$(CC) $(INCLUDEFLAGS) -c -o $@ $^

clean:
	$(RM) -r $(OBJDIR) $(BINDIR)