
binary-objs = binary.o

all: binary

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

binary: $(binary-objs)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) -o $@ $^
