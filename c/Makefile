prefix=/usr
DESTDIR=$(shell pwd)/destdir

bin=$(prefix)/bin
sbin=$(prefix)/sbin

all:

helloworld: helloworld.o
	$(CC) $(CFLAGS) -o $@ $<

environment: environment.o
	$(CC) $(CFLAGS) -o $@ $<

system: system.o
	$(CC) $(CFLAGS) -o $@ $<

readlink: readlink.o
	$(CC) $(CFLAGS) -o $@ $<

all: helloworld environment system readlink

clean:
	-rm -f *.o
	-rm -f helloworld environment system readlink
	-rm -f -r $(DESTDIR)

install: helloworld environment system readlink
	@install -d $(DESTDIR)$(bin)
	@install -t $(DESTDIR)$(bin) helloworld environment system readlink
	