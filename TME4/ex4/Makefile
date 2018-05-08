CC= gcc
CFLAGS= -Wall -std=gnu99
LDLIBS= -linrimage
SRC= filtreMedian.c
OBJ=$(SRC:.c=.o)

all: filtreMedian

clean:
	rm -f $(OBJ) filtreMedian
re: clean all

.phony: all clean re
