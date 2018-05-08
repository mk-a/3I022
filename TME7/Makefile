CC= gcc
CFLAGS = -Wall -std=gnu99
LDLIBS= -linrimage -lm
SRC= hough.c linkedlist.c functions.c houghcircle.c linkedlist2.c
OBJ= $(SRC:.c=.o)

all: hough houghcircle

hough: hough.o linkedlist.o

houghcircle: houghcircle.o linkedlist2.o

clean:
	rm -rf $(OBJ) hough houghcircle

re: clean all

.phony: all clean re
