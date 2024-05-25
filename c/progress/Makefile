
ECHO ?= echo
CFLAGS ?= -g



all:

%.o: %.c
	@$(ECHO) [CC] $^
	@$(CC) -c $(CFLAGS) $(CPPFLAGS) $^


worker: worker.o
	@$(ECHO) [LD] $@
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LIBS)
	

all: worker


clean:
	-rm -f *.o
	-rm -f worker

.PHONY: all clean

