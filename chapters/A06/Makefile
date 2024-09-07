CC = gcc
CFLAGS = -Wall -Wextra -O2
AR = ar
ARFLAGS = rcs

LIB_NAME = libcomplex.a
SRC = complex.c
OBJ = $(SRC:.c=.o)
HEADER = complex.h

.PHONY: all clean install

all: $(LIB_NAME)

$(LIB_NAME): $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

install: $(LIB_NAME)
	install -m 644 $(LIB_NAME) /usr/local/lib/
	install -m 644 $(HEADER) /usr/local/include/

clean:
	rm -f $(OBJ) $(LIB_NAME)
