CC = gcc
CFLAGS = -g -O1 -fsanitize=address -fno-omit-frame-pointer -Wall -Wextra -I . -o sim
TARGET = sim
SOURCES= init.c terminal.c fileio.c textio.c commands.c cursor.c display.c
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

$.o: $.c
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

