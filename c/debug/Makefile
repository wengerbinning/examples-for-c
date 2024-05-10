ECHO ?= echo
CC   ?= gcc

CPPFLAGS ?= -I/usr/local/lib
LDFLAGS	 ?= -L/usr/local/lib
LIBS     ?= -ldevel

CFLAGS  ?= -g -fPIC

all:

%.o: %.c
	@$(ECHO) [CC] $@
	@$(CC) -c $(CFLAGS) $(CPPFLAGS) $^

libdevel.so: devel.o
	@$(ECHO) [LD] $@
	@$(CC) -shared -o $@ $^

main: main.o
	@$(ECHO) [LD] $@
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

all: main libdevel.so

clean: FORCE
	-rm -f *.o

.PHONY: all clean

FORCE: