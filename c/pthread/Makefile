ECHO ?= echo

CFLAGS   := -g
CPPFLAGS := -Iinclude

LIBS := -lcurl

all:

%.o: %.c
	@$(ECHO) [CC] $<
	@$(CC) -c $(CFLAGS) $(CPPFLAGS) $<

thread: main.o thread_download.o url.o
	@$(ECHO) [LD] $@
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)


all: thread FORCE

clean:
	-rm -f *.o

.PHONY: all clean
FORCE: