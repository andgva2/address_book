CC = gcc
CFLAGS = -g -Wall
TARGET = address_book
BINDIR = ./bin

SRCSDIR = ./src
SRCS = $(TARGET).c liblinkedlist.c
OBJSDIR = ./obj
OBJS = $(addprefix $(OBJSDIR)/, $(SRCS:.c=.o))

INCLUDES = -I$(SRCSDIR)/

LFLAGS = -L./lib/
LIBS = -llinkedlist

all: $(TARGET)
	
$(TARGET): $(OBJS)
	mkdir -p $(BINDIR)/
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BINDIR)/$(TARGET) $(SRCSDIR)/$(TARGET).c

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c
	mkdir -p $(OBJSDIR)/
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) -r $(BINDIR)/ $(OBJSDIR)/
