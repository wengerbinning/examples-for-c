
ECHO ?= echo

CC   ?= gcc


all:




%.o: %.c
	@$(ECHO) [CC] $^
	@$(CC) -c $(CFLAGS) $(CPPFLAGS) $^

LIBS += -lubox

ulog: ulog.o
	@$(ECHO) [LD] $@
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LIBS)

klist: klist.o
	@$(ECHO) [LD] $@
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LIBS)

all: ulog klist FORCE


.PHONY: all
FORCE: