CC= gcc
CFLAGS= -Wall -std=gnu99
LDLIBS= -linrimage -lm
SRC= harris.c functions.c
OBJ= $(SRC:.c=.o)


all: harris sloc

sloc: sloc.c

harris: $(OBJ)

clean:
	rm -f $(OBJ) harris
re: clean all

.phony: all re clean
