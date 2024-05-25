


ECHO ?= echo
CC   ?= gcc

CFLAGS      ?=
CPPFLAGS    ?=
LDFLAGS     ?=
LIBS        ?=




all:



%.o: %.c
	@$(ECHO) [CC] $^
	@$(CC) -c $(CFLAGS) $(CPPFLAGS) $^

worker: main.o
	@$(ECHO) [LD] $@
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LIBS)


all: worker



clean:
	-rm -f *.o

.PHONY: all clean
FORCE: