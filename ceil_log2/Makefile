CC = gcc
CFLAGS = -g  

OBJS := main.o
TARGETS := main

test: $(TARGETS)
	python3 test.py

$(TARGETS): $(OBJS)
	$(CC) -o $@ $(CFLAGS) $^

%.o: %.c
	$(CC) -o $@ $(CFLAGS) -c $^

clean:
	rm -f $(OBJS)
	rm -f $(TARGETS)
