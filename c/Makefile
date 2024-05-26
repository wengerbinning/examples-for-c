
ECHO    ?= echo
CC      ?= gcc
#
CFLAGS   ?= -g
CPPFLAGS ?= -Iinclude
LIBS     ?= -lcurl
#
prefix  ?=/usr
DESTDIR ?=$(shell pwd)/destdir
#
bin     ?= $(prefix)/bin
sbin    ?= $(prefix)/sbin
include ?= $(prefix)/include
lib     ?= $(prefix)/lib


##
all:

%.o: %.c
	@$(ECHO) [CC] $<
	@$(CC) -c $(CFLAGS) $(CPPFLAGS) $<

##
progs := helloworld
helloworld: helloworld.o
	@$(ECHO) [LD] $@
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LIBS)

progs += environment
environment: environment.o
	@$(ECHO) [LD] $@
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LIBS)

progs += readlink
readlink: readlink.o
	@$(ECHO) [LD] $@
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LIBS)


progs += server
server: usock0.o
	@$(ECHO) [LD] $@
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LIBS)

progs += client
client: usock1.o
	@$(ECHO) [LD] $@
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LIBS)

progs += regex
regex: regex.o
	@$(ECHO) [LD] $@
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LIBS)

##
all: $(progs)

clean: FORCE
	-rm -f *.o
	-rm -f $(progs)

install: $(progs)
	install -d $(DESTDIR)$(bin)
	install -t $(DESTDIR)$(bin) $(progs)

.PHONY: all clean install
FORCE: