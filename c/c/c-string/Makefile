

ECHO := echo

CC := gcc

CFLAGS := -g

all: string



%.o: %.c
	@$(ECHO) [CC] $^
	@$(CC) $(CFLAGS) $(CPPLAGS) -c $<

string: string.o string-escape.o
	@$(ECHO) [LD] $@
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)


string-clean:
	-rm -rf string

clean: string-clean
	-rm -rf *.o