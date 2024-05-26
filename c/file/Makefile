ECHO ?= echo

CFLAGS   := -g
CPPFLAGS := -Iinclude

# LIBS := -lcurl

all:

%.o: %.c
	@$(ECHO) [CC] $<
	@$(CC) -c $(CFLAGS) $(CPPFLAGS) $<

progs := parse
parse: main.o
	@$(ECHO) [LD] $@
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)


all: $(progs) FORCE

clean:
	-rm -f *.o
	-rm -f $(progs)

.PHONY: all clean
FORCE: