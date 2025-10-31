CC = gcc
PREREQS = ../include/defs.h
SOURCES= init.c terminal.c fileio.c textio.c commands.c cursor.c display.c
CFLAGS = -I ../include/

sim: ${PREREQS}
	echo `[ -f "../include/defs.h" ]`
	${CC} ${CFLAGS} ${SOURCES}

clean:
	echo "clean"

