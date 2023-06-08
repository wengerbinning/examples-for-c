ECHO := echo

CFLAGS := -g

LIBS := -lfcgi

all: server


%.o: %.c
	@(ECHO) [CC] $^
	@$(CC) -c $(CFLAGS) $(CFLAGS) $^

server: server.o
	@(ECHO) [LD] $@
	@(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)


clean:
	-rm -rf *.o *.a *.so