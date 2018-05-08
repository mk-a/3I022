CC=gcc
CFLAGS= -Wall -std=gnu99
LDLIBS= -linrimage -lm

SRC= inrimage.c
OBJ=$(SRC:.c=.o)
all: inrimage
clean:
	rm -rf $(OBJ) inrimage
re: clean all
.phony: all clean re
