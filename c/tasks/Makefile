
CC := gcc

all:

*.o: *.c
	$(CC) -c -o $@ $<

helloworld: helloworld.o
	$(CC) -o $@ $^


all: helloworld



clean:
	rm -rf *.o