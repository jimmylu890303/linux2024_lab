CC = gcc
CFLAGS = -g -Wall -lm

OBJS := main.o

all: lru


lru: $(OBJS)
	$(CC) -o $@ $^ -lm


%.o: %.c
	$(CC) -o $@ $(CFLAGS) -c $^

clean:
	rm -f $(OBJS)
	rm -f lru
