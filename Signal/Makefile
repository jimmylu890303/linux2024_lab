CC = gcc

CFLAGS = -Wall -g

TARGETS = unreliable reliable sender

all: $(TARGETS)

unreliable: unreliable.o
	$(CC) $(CFLAGS) -o unreliable unreliable.o

reliable: reliable.o
	$(CC) $(CFLAGS) -o reliable reliable.o

sender: sender.o
	$(CC) $(CFLAGS) -o sender sender.o

unreliable.o: unreliable.c
	$(CC) $(CFLAGS) -c unreliable.c

reliable.o: reliable.c
	$(CC) $(CFLAGS) -c reliable.c

sender.o: sender.c
	$(CC) $(CFLAGS) -c sender.c

clean:
	rm -f $(TARGETS) *.o


