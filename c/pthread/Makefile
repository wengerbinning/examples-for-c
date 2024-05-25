ECHO ?= echo

CFLAGS   ?= -g
CPPFLAGS ?= -Iinclude
LIBS     ?= -lcurl

all:

%.o: %.c
	@$(ECHO) [CC] $<
	@$(CC) -c $(CFLAGS) $(CPPFLAGS) $<

client: client.o thread_download.o url.o
	@$(ECHO) [LD] $@
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

all: client FORCE

clean:
	-rm -f *.o

.PHONY: all clean
FORCE: