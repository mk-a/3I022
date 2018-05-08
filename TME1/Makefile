CC=gcc
CFLAGS= -Wall -std=gnu99
SRC= pgm.c main.c histogram.c etire.c seuillage.c
OBJ=$(SRC:.c=.o)

all: main

main: $(OBJ)

clean:
	rm -r $(OBJ) main

re: clean all

.phony= all clean re
