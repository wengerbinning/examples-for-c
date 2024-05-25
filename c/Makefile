
prefix  ?=/usr
DESTDIR ?=$(shell pwd)/destdir

bin     ?= $(prefix)/bin
sbin    ?= $(prefix)/sbin
include ?= $(prefix)/include
lib     ?= $(prefix)/lib

all:

%.o: %.c
	@echo [CC] $^
	@$(CC) -c $(CFLAGS) $(CPPFLAGS) $^

##
progs := helloworld
helloworld: helloworld.o
	@echo [LD] $@
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LIBS)

progs += environment
environment: environment.o
	@echo [LD] $@
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LIBS)

progs += readlink
readlink: readlink.o
	@echo [LD] $@
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LIBS)



##
all: $(progs)

clean: FORCE
	-rm -rf *.o
	-rm -rf $(progs)

install: $(progs)
	install -d $(DESTDIR)$(bin)
	install -t $(DESTDIR)$(bin) $(progs)
	
.PHONY: all clean install
FORCE: